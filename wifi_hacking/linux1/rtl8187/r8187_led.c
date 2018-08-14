/*++
Copyright (c) Realtek Semiconductor Corp. All rights reserved.

Module Name:
 	r8187_led.c
	
Abstract:
 	RTL8187 LED control functions
 	    
Major Change History:
	When        Who      What
	----------    ---------------   -------------------------------
	2006-09-07    Xiong		Created
    
Notes:	
 	
--*/

/*--------------------------Include File------------------------------------*/
#include "r8180_hw.h"
#include "r8187.h"
#include "r8180_93cx6.h" 
#include "r8187_led.h"


/**
*
* Initialization function for Sw Leds controll. 
* 
* \param dev      The net device for this driver.
* \return void.
*
* Note: 
* 
*/
void
InitSwLeds(
	struct net_device *dev
	)
{
	struct r8180_priv *priv = ieee80211_priv(dev);
	u16	usValue;

	priv->CustomerID = RT_CID_DEFAULT; //just set to default now
	priv->bEnableLedCtrl = 1;
	priv->PsrValue = read_nic_byte(dev, PSR);
	usValue = eprom_read(dev, EEPROM_SW_REVD_OFFSET >> 1);
	priv->EEPROMCustomerID = (u8)( usValue & EEPROM_CID_MASK );
	DMESG("EEPROM Customer ID: %02X\n", priv->EEPROMCustomerID);

	if(priv->CustomerID == RT_CID_DEFAULT)
	{ // If we have not yet change priv->CustomerID in register, 
	  // we initialzie it from that of EEPROM with proper translation, 2006.07.03, by rcnjko.
		switch(priv->EEPROMCustomerID)
		{
		case EEPROM_CID_RSVD0:
		case EEPROM_CID_RSVD1:
			priv->CustomerID = RT_CID_DEFAULT;
			break;
	
		case EEPROM_CID_ALPHA0:
			priv->CustomerID = RT_CID_8187_ALPHA0;
			break;
	
		case EEPROM_CID_SERCOMM_PS:
			priv->CustomerID = RT_CID_8187_SERCOMM_PS;
			break;
	
		case EEPROM_CID_HW_LED:
			priv->CustomerID = RT_CID_8187_HW_LED;
			break;
	
		default:
			// Invalid value, so, we use default value instead.
			priv->CustomerID = RT_CID_DEFAULT;
			break;
		}
	}
	switch(priv->CustomerID)
	{
	case RT_CID_DEFAULT: 
		priv->LedStrategy = SW_LED_MODE0;
		break;
	
	case RT_CID_8187_ALPHA0:
		priv->LedStrategy = SW_LED_MODE1;
		break;	

	case RT_CID_8187_SERCOMM_PS:
		priv->LedStrategy = SW_LED_MODE3;
		break;

	case RT_CID_8187_HW_LED:
		priv->LedStrategy = HW_LED;
		break;

	default:
		priv->LedStrategy = SW_LED_MODE0;
		break;
	}
	
	InitLed8187(dev, 
				&(priv->Gpio0Led), 
				LED_PIN_GPIO0, 
				Gpio0LedBlinkTimerCallback);
	INIT_WORK(&priv->Gpio0LedWorkItem, 
				(void(*)(void*))Gpio0LedWorkItemCallback, dev);

	InitLed8187(dev,
				&(priv->SwLed0), 
				LED_PIN_LED0, 
				SwLed0BlinkTimerCallback);
	INIT_WORK(&priv->SwLed0WorkItem, 
				(void(*)(void*))SwLed0WorkItemCallback, dev);

	InitLed8187(dev,
				&(priv->SwLed1), 
				LED_PIN_LED1, 
				SwLed1BlinkTimerCallback);
	INIT_WORK(&priv->SwLed1WorkItem, 
				(void(*)(void*))SwLed1WorkItemCallback, dev);
}

void
DeInitSwLeds(
	struct net_device *dev
	)
{
	struct r8180_priv *priv = ieee80211_priv(dev);

	DeInitLed8187(dev, &(priv->Gpio0Led));
	DeInitLed8187(dev, &(priv->SwLed0));
	DeInitLed8187(dev, &(priv->SwLed1));
}

void
InitLed8187(
	struct net_device *dev, 
	PLED_8187		pLed,
	LED_PIN_8187		LedPin,
	void	* 		BlinkCallBackFunc)
{
	pLed->LedPin = LedPin;

	pLed->bLedOn = 0;
	pLed->CurrLedState = LED_OFF;

	pLed->bLedBlinkInProgress = 0;
	pLed->BlinkTimes = 0;
	pLed->BlinkingLedState = LED_OFF;

	init_timer(&(pLed->BlinkTimer));
	pLed->BlinkTimer.data = (unsigned long)dev;
	pLed->BlinkTimer.function = BlinkCallBackFunc;
	//PlatformInitializeTimer(dev, &(pLed->BlinkTimer), BlinkCallBackFunc);
}

void
DeInitLed8187(
	struct net_device *dev, 
	PLED_8187			pLed)
{
	//PlatformCancelTimer(dev, &(pLed->BlinkTimer));
	del_timer_sync(&(pLed->BlinkTimer));
	// We should reset bLedBlinkInProgress if we cancel the LedControlTimer, 2005.03.10, by rcnjko.
	pLed->bLedBlinkInProgress = 0;
}

void
LedControl8187(
	struct net_device *dev,
	LED_CTL_MODE		LedAction
)
{
	struct r8180_priv *priv = ieee80211_priv(dev);

	if( priv->bEnableLedCtrl == 0)
		return;

/*
	if(	priv->eRFPowerState != eRfOn && 
		(LedAction == LED_CTL_TX || LedAction == LED_CTL_RX || 
		 LedAction == LED_CTL_SITE_SURVEY || 
		 LedAction == LED_CTL_LINK || 
		 LedAction == LED_CTL_NO_LINK) )
	{
		return;
	}
*/

	switch(priv->LedStrategy)
	{
	case SW_LED_MODE0:
		SwLedControlMode0(dev, LedAction);
		break;

	case SW_LED_MODE1:
		SwLedControlMode1(dev, LedAction);
		break;

	case SW_LED_MODE2:
		SwLedControlMode2(dev, LedAction);
		break;

	case SW_LED_MODE3:
		SwLedControlMode3(dev, LedAction);
		break;

	default:
		break;
	}
}


//
//	Description:	
//		Implement each led action for SW_LED_MODE0.
//		This is default strategy.
//
void
SwLedControlMode0(
	struct net_device *dev,
	LED_CTL_MODE		LedAction
)
{
	struct r8180_priv *priv = ieee80211_priv(dev);
	PLED_8187 pLed = &(priv->Gpio0Led);

	// Decide led state
	switch(LedAction)
	{
	case LED_CTL_TX:
	case LED_CTL_RX:
		if( pLed->bLedBlinkInProgress == 0 )
		{
			pLed->CurrLedState = LED_BLINK_NORMAL;
			pLed->BlinkTimes = 2;
		}
		else
		{
			return;
		}
		break;

	case LED_CTL_SITE_SURVEY:
		if( pLed->bLedBlinkInProgress == 0 )
		{
			pLed->CurrLedState = LED_BLINK_SLOWLY;
			pLed->BlinkTimes = 10;
		}
		else
		{
			return;
		}
		break;

	case LED_CTL_LINK:
		pLed->CurrLedState = LED_ON;
		break;

	case LED_CTL_NO_LINK:
		pLed->CurrLedState = LED_OFF;
		break;
	
	case LED_CTL_POWER_ON:
		pLed->CurrLedState = LED_POWER_ON_BLINK;
		break;

	case LED_CTL_POWER_OFF:
		pLed->CurrLedState = LED_OFF;
		break;

	default:
		return;
		break;
	}

	// Change led state.
	switch(pLed->CurrLedState)
	{
	case LED_ON:
		if( pLed->bLedBlinkInProgress == 0 )
		{
			SwLedOn(dev, pLed);
		}
		break;

	case LED_OFF:
		if( pLed->bLedBlinkInProgress == 0 )
		{
			SwLedOff(dev, pLed);
		}
		break;

	case LED_BLINK_NORMAL:
		if( pLed->bLedBlinkInProgress == 0 )
		{
			pLed->bLedBlinkInProgress = 1;
			if( pLed->bLedOn )
				pLed->BlinkingLedState = LED_OFF; 
			else
				pLed->BlinkingLedState = LED_ON; 
			
			pLed->BlinkTimer.expires = jiffies + LED_BLINK_NORMAL_INTERVAL;
			add_timer(&(pLed->BlinkTimer));
			//PlatformSetTimer(dev, &(pLed->BlinkTimer), LED_BLINK_NORMAL_INTERVAL);
		}
		break;

	case LED_BLINK_SLOWLY:
		if( pLed->bLedBlinkInProgress == 0 )
		{
			pLed->bLedBlinkInProgress = 1;
			if( pLed->bLedOn )
				pLed->BlinkingLedState = LED_OFF; 
			else
				pLed->BlinkingLedState = LED_ON;
			
			pLed->BlinkTimer.expires = jiffies + LED_BLINK_SLOWLY_INTERVAL;
			add_timer(&(pLed->BlinkTimer));
			//PlatformSetTimer(dev, &(pLed->BlinkTimer), LED_BLINK_SLOWLY_INTERVAL);
		}
		break;

	case LED_POWER_ON_BLINK:
		SwLedOn(dev, pLed);
		mdelay(100);
		SwLedOff(dev, pLed);
		break;

	default:
		break;
	}
}

//
//	Description:	
//		Implement each led action for SW_LED_MODE1.
//		For example, this is applied by ALPHA.
//
void
SwLedControlMode1(
	struct net_device *dev,
	LED_CTL_MODE		LedAction
)
{
	struct r8180_priv *priv = ieee80211_priv(dev);
	PLED_8187 pLed0 = &(priv->SwLed0);
	PLED_8187 pLed1 = &(priv->SwLed1);

	switch(LedAction)
	{
	case LED_CTL_TX:
		if( pLed0->bLedBlinkInProgress == 0 )
		{
			pLed0->CurrLedState = LED_BLINK_NORMAL;
			pLed0->BlinkTimes = 2;
			pLed0->bLedBlinkInProgress = 1;
			if( pLed0->bLedOn )
				pLed0->BlinkingLedState = LED_OFF; 
			else
				pLed0->BlinkingLedState = LED_ON; 

			pLed0->BlinkTimer.expires = jiffies + LED_BLINK_NORMAL_INTERVAL;
			add_timer(&(pLed0->BlinkTimer));
			//PlatformSetTimer(dev, &(pLed0->BlinkTimer), LED_BLINK_NORMAL_INTERVAL);
		}
		break;

	case LED_CTL_LINK:
		pLed0->CurrLedState = LED_ON;
		if( pLed0->bLedBlinkInProgress == 0 )
		{
			SwLedOn(dev, pLed0);
		}
		break;

	case LED_CTL_NO_LINK:
		pLed0->CurrLedState = LED_OFF;
		if( pLed0->bLedBlinkInProgress == 0 )
		{
			SwLedOff(dev, pLed0);
		}
		break;
	
	case LED_CTL_POWER_ON:
		pLed0->CurrLedState = LED_OFF;
		SwLedOff(dev, pLed0);

		pLed1->CurrLedState = LED_ON;
		SwLedOn(dev, pLed1);

		break;

	case LED_CTL_POWER_OFF:
		pLed0->CurrLedState = LED_OFF;
		SwLedOff(dev, pLed0);

		pLed1->CurrLedState = LED_OFF;
		SwLedOff(dev, pLed1);
		break;

	case LED_CTL_SITE_SURVEY:
		if( pLed0->bLedBlinkInProgress == 0 )
		{
			pLed0->CurrLedState = LED_BLINK_SLOWLY;;
			pLed0->BlinkTimes = 10;
			pLed0->bLedBlinkInProgress = 1;
			if( pLed0->bLedOn )
				pLed0->BlinkingLedState = LED_OFF; 
			else
				pLed0->BlinkingLedState = LED_ON;

			pLed0->BlinkTimer.expires = jiffies + LED_BLINK_SLOWLY_INTERVAL;
			add_timer(&(pLed0->BlinkTimer));
			//PlatformSetTimer(dev, &(pLed0->BlinkTimer), LED_BLINK_SLOWLY_INTERVAL);
		}
		break;

	default:
		break;
	}
}

//
//	Description:	
//		Implement each led action for SW_LED_MODE2, 
//		which is customized for AzWave 8187 minicard.  
//		2006.04.03, by rcnjko.
//
void
SwLedControlMode2(
	struct net_device *dev,
	LED_CTL_MODE		LedAction
)
{
	struct r8180_priv *priv = ieee80211_priv(dev);
	PLED_8187 pLed = &(priv->Gpio0Led);

	// Decide led state
	switch(LedAction)
	{
	case LED_CTL_TX:
	case LED_CTL_RX:
		if( pLed->bLedBlinkInProgress == 0 )
		{
			pLed->bLedBlinkInProgress = 1;

			pLed->CurrLedState = LED_BLINK_NORMAL;
			pLed->BlinkTimes = 2;

			if( pLed->bLedOn )
				pLed->BlinkingLedState = LED_OFF; 
			else
				pLed->BlinkingLedState = LED_ON; 

			pLed->BlinkTimer.expires = jiffies + LED_BLINK_NORMAL_INTERVAL;
			add_timer(&(pLed->BlinkTimer));
			//PlatformSetTimer(dev, &(pLed->BlinkTimer), LED_BLINK_NORMAL_INTERVAL);
		}
		break;

	case LED_CTL_SITE_SURVEY:
		if( pLed->bLedBlinkInProgress == 0 )
		{
			pLed->bLedBlinkInProgress = 1;

			//if(	dev->MgntInfo.mAssoc || 
			//	dev->MgntInfo.mIbss )
			//{
				pLed->CurrLedState = LED_SCAN_BLINK;
				pLed->BlinkTimes = 4;
			//}
			//else
			//{
			//	pLed->CurrLedState = LED_NO_LINK_BLINK;
			//	pLed->BlinkTimes = 24;
			//}

			if( pLed->bLedOn )
			{
				pLed->BlinkingLedState = LED_OFF;
				pLed->BlinkTimer.expires = jiffies + LED_CM2_BLINK_ON_INTERVAL;
				add_timer(&(pLed->BlinkTimer));
				//PlatformSetTimer(dev, &(pLed->BlinkTimer), LED_CM2_BLINK_ON_INTERVAL);
			}
			else
			{
				pLed->BlinkingLedState = LED_ON; 
				pLed->BlinkTimer.expires = jiffies + LED_CM2_BLINK_OFF_INTERVAL;
				add_timer(&(pLed->BlinkTimer));
				//PlatformSetTimer(dev, &(pLed->BlinkTimer), LED_CM2_BLINK_OFF_INTERVAL);
			}
		}
		else
		{
			if(pLed->CurrLedState != LED_NO_LINK_BLINK)
			{
				pLed->CurrLedState = LED_SCAN_BLINK;
				/*
				if(	dev->MgntInfo.mAssoc || 
					dev->MgntInfo.mIbss )
				{
					pLed->CurrLedState = LED_SCAN_BLINK;
				}
				else
				{
					pLed->CurrLedState = LED_NO_LINK_BLINK;
				}
				*/
			}
		}
		break;

	case LED_CTL_NO_LINK:
		if( pLed->bLedBlinkInProgress == 0 )
		{
			pLed->bLedBlinkInProgress = 1;

			pLed->CurrLedState = LED_NO_LINK_BLINK;
			pLed->BlinkTimes = 24;

			if( pLed->bLedOn )
			{
				pLed->BlinkingLedState = LED_OFF; 
				pLed->BlinkTimer.expires = jiffies + LED_CM2_BLINK_ON_INTERVAL;
				add_timer(&(pLed->BlinkTimer));
				//PlatformSetTimer(dev, &(pLed->BlinkTimer), LED_CM2_BLINK_ON_INTERVAL);
			}
			else
			{
				pLed->BlinkingLedState = LED_ON; 
				pLed->BlinkTimer.expires = jiffies + LED_CM2_BLINK_OFF_INTERVAL;
				add_timer(&(pLed->BlinkTimer));
				//PlatformSetTimer(dev, &(pLed->BlinkTimer), LED_CM2_BLINK_OFF_INTERVAL);
			}
		}
		else
		{
			pLed->CurrLedState = LED_NO_LINK_BLINK;
		}
		break;

	case LED_CTL_LINK:
		pLed->CurrLedState = LED_ON;
		if( pLed->bLedBlinkInProgress == 0 )
		{
			SwLedOn(dev, pLed);
		}
		break;

	case LED_CTL_POWER_OFF:
		pLed->CurrLedState = LED_OFF;
		if( pLed->bLedBlinkInProgress == 0 )
		{
			SwLedOff(dev, pLed);
		}
		break;

	default:
		break;
	}
}


//
//	Description:	
//		Implement each led action for SW_LED_MODE3, 
//		which is customized for Sercomm Printer Server case. 
//		2006.04.21, by rcnjko.
//
void
SwLedControlMode3(
	struct net_device *dev,
	LED_CTL_MODE		LedAction
)
{
	struct r8180_priv *priv = ieee80211_priv(dev);
	PLED_8187 pLed = &(priv->Gpio0Led);

	// Decide led state
	switch(LedAction)
	{
	case LED_CTL_TX:
	case LED_CTL_RX:
		if( pLed->bLedBlinkInProgress == 0 )
		{
			pLed->bLedBlinkInProgress = 1;

			pLed->CurrLedState = LED_BLINK_CM3;
			pLed->BlinkTimes = 2;

			if( pLed->bLedOn )
				pLed->BlinkingLedState = LED_OFF; 
			else
				pLed->BlinkingLedState = LED_ON; 

			pLed->BlinkTimer.expires = jiffies + LED_CM3_BLINK_INTERVAL;
			add_timer(&(pLed->BlinkTimer));
			//PlatformSetTimer(dev, &(pLed->BlinkTimer), LED_CM3_BLINK_INTERVAL);
		}
		break;

	case LED_CTL_SITE_SURVEY:
		if( pLed->bLedBlinkInProgress == 0 )
		{
			pLed->bLedBlinkInProgress = 1;

			pLed->CurrLedState = LED_BLINK_CM3;
			pLed->BlinkTimes = 10;

			if( pLed->bLedOn )
				pLed->BlinkingLedState = LED_OFF; 
			else
				pLed->BlinkingLedState = LED_ON; 

			pLed->BlinkTimer.expires = jiffies + LED_CM3_BLINK_INTERVAL;
			add_timer(&(pLed->BlinkTimer));
			//PlatformSetTimer(dev, &(pLed->BlinkTimer), LED_CM3_BLINK_INTERVAL);
		}
		break;

	case LED_CTL_LINK:
		pLed->CurrLedState = LED_ON;
		if( pLed->bLedBlinkInProgress == 0 )
		{
			SwLedOn(dev, pLed);
		}
		break;

	case LED_CTL_NO_LINK:
		pLed->CurrLedState = LED_OFF;
		if( pLed->bLedBlinkInProgress == 0 )
		{
			SwLedOff(dev, pLed);
		}
		break;

	case LED_CTL_POWER_ON:
		pLed->CurrLedState = LED_POWER_ON_BLINK;
		SwLedOn(dev, pLed);
		mdelay(100);
		SwLedOff(dev, pLed);
		break;

	case LED_CTL_POWER_OFF:
		pLed->CurrLedState = LED_OFF;
		if( pLed->bLedBlinkInProgress == 0 )
		{
			SwLedOff(dev, pLed);
		}
		break;

	default:
		break;
	}
}

//
// Callback fuction of the timer, Gpio0Led.BlinkTimer.
//
void
Gpio0LedBlinkTimerCallback(
	unsigned long		data
	)
{
	struct net_device *dev = (struct net_device *)data;
	struct r8180_priv *priv = ieee80211_priv(dev);

	PlatformSwLedBlink(dev, &(priv->Gpio0Led));
}



//
// Callback fuction of the timer, SwLed0.BlinkTimer.
//
void
SwLed0BlinkTimerCallback(
	unsigned long		data
	)
{
	struct net_device *dev = (struct net_device *)data;
	struct r8180_priv *priv = ieee80211_priv(dev);

	PlatformSwLedBlink(dev, &(priv->SwLed0));
}



//
// Callback fuction of the timer, SwLed1.BlinkTimer.
//
void
SwLed1BlinkTimerCallback(
	unsigned long		data
	)
{
	struct net_device *dev = (struct net_device *)data;
	struct r8180_priv *priv = ieee80211_priv(dev);

	PlatformSwLedBlink(dev, &(priv->SwLed1));
}

void
PlatformSwLedBlink(
	struct net_device *dev,
	PLED_8187		pLed
	)
{
	struct r8180_priv *priv = ieee80211_priv(dev);

	switch(pLed->LedPin)
	{
	case LED_PIN_GPIO0:
		schedule_work(&(priv->Gpio0LedWorkItem));
		break;

	case LED_PIN_LED0:
		schedule_work(&(priv->SwLed0WorkItem));
		break;

	case LED_PIN_LED1:
		schedule_work(&(priv->SwLed1WorkItem));
		break;

	default:
		break;
	}
}

// 
// Callback fucntion of the workitem for SW LEDs.
// 2006.03.01, by rcnjko.
//
void
Gpio0LedWorkItemCallback(
	void *			Context
	)
{
	struct net_device *dev = (struct net_device *)Context;
	struct r8180_priv *priv = ieee80211_priv(dev);
	PLED_8187	pLed = &(priv->Gpio0Led); 

	if(priv->LedStrategy == SW_LED_MODE2)
		SwLedCm2Blink(dev, pLed);
	else
		SwLedBlink(dev, pLed);

	//LeaveCallbackOfRtWorkItem( &(usbdevice->Gpio0LedWorkItem) );
}

void
SwLed0WorkItemCallback(
	void *			Context
	)
{
	struct net_device *dev = (struct net_device *)Context;
	struct r8180_priv *priv = ieee80211_priv(dev);

	SwLedBlink(dev, &(priv->SwLed0));

	//LeaveCallbackOfRtWorkItem( &(usbdevice->SwLed0WorkItem) );
}

void
SwLed1WorkItemCallback(
	void *			Context
	)
{
	struct net_device *dev = (struct net_device *)Context;
	struct r8180_priv *priv = ieee80211_priv(dev);

	SwLedBlink(dev, &(priv->SwLed1));

	//LeaveCallbackOfRtWorkItem( &(usbdevice->SwLed1WorkItem) );
}

//
//	Implementation of LED blinking behavior.
//	It toggle off LED and schedule corresponding timer if necessary.
//
void
SwLedBlink(
	struct net_device *dev, 
	PLED_8187			pLed
	)
{
	u8 bStopBlinking = 0;

	// Change LED according to BlinkingLedState specified.
	if( pLed->BlinkingLedState == LED_ON ) 
	{
		SwLedOn(dev, pLed);
		//DMESG("Blinktimes (%d): turn on\n", pLed->BlinkTimes);
	}	
	else 
	{
		SwLedOff(dev, pLed);
		//DMESG("Blinktimes (%d): turn off\n", pLed->BlinkTimes);
	}

	// Determine if we shall change LED state again.
	pLed->BlinkTimes--;
	if(	pLed->BlinkTimes == 0 )
	{
		bStopBlinking = 1;
	}
	else
	{
		if(	pLed->CurrLedState != LED_BLINK_NORMAL &&
			pLed->CurrLedState != LED_BLINK_SLOWLY &&
			pLed->CurrLedState != LED_BLINK_CM3	)
		{
			bStopBlinking = 1;
		}
	}

	if(bStopBlinking)
	{
		if(	pLed->CurrLedState == LED_ON && pLed->bLedOn == 0)
		{
			SwLedOn(dev, pLed);
		}
		else if(pLed->CurrLedState == LED_OFF && pLed->bLedOn == 1)
		{
			SwLedOff(dev, pLed);
		}

		pLed->BlinkTimes = 0;
		pLed->bLedBlinkInProgress = 0;	
	}
	else
	{
		// Assign LED state to toggle.
		if( pLed->BlinkingLedState == LED_ON ) 
			pLed->BlinkingLedState = LED_OFF;
		else 
			pLed->BlinkingLedState = LED_ON;

		// Schedule a timer to toggle LED state. 
		switch( pLed->CurrLedState )
		{
		case LED_BLINK_NORMAL:
			pLed->BlinkTimer.expires = jiffies + LED_BLINK_NORMAL_INTERVAL;
			add_timer(&(pLed->BlinkTimer));		
			//PlatformSetTimer(dev, &(pLed->BlinkTimer), LED_BLINK_NORMAL_INTERVAL);
			break;

		case LED_BLINK_SLOWLY:
			pLed->BlinkTimer.expires = jiffies + LED_BLINK_SLOWLY_INTERVAL;
			add_timer(&(pLed->BlinkTimer));			
			//PlatformSetTimer(dev, &(pLed->BlinkTimer), LED_BLINK_SLOWLY_INTERVAL);
			break;

		case LED_BLINK_CM3:
			pLed->BlinkTimer.expires = jiffies + LED_CM3_BLINK_INTERVAL;
			add_timer(&(pLed->BlinkTimer));			
			//PlatformSetTimer(dev, &(pLed->BlinkTimer), LED_CM3_BLINK_INTERVAL);
			break;

		default:
			pLed->BlinkTimer.expires = jiffies + LED_BLINK_SLOWLY_INTERVAL;
			add_timer(&(pLed->BlinkTimer));			
			//PlatformSetTimer(dev, &(pLed->BlinkTimer), LED_BLINK_SLOWLY_INTERVAL);
			break;
		}
	}
}



//
//	Implementation of LED blinking behavior for SwLedControlMode2. 
//
void
SwLedCm2Blink(
	struct net_device *dev, 
	PLED_8187			pLed
	)
{
	//struct r8180_priv *priv = ieee80211_priv(dev);
	//PMGNT_INFO priv = &(dev->MgntInfo);
	u8 bStopBlinking = 0;

	// Change LED according to BlinkingLedState specified.
	if( pLed->BlinkingLedState == LED_ON ) 
	{
		SwLedOn(dev, pLed);
		//DMESG("Blinktimes (%d): turn on\n", pLed->BlinkTimes);
	}	
	else 
	{
		SwLedOff(dev, pLed);
		//DMESG("Blinktimes (%d): turn off\n", pLed->BlinkTimes);
	}

	// Determine if we shall change LED state again.
	pLed->BlinkTimes--;
	switch(pLed->CurrLedState)
	{
	case LED_BLINK_NORMAL: 
		if(pLed->BlinkTimes == 0)
		{
			bStopBlinking = 1;
		}
		break;
/* CM2 scan blink and no link blind now not be supported 
	case LED_SCAN_BLINK:
		if( (priv->mAssoc || priv->mIbss) &&  // Linked.
			(!priv->bScanInProgress) && // Not in scan stage.
			(pLed->BlinkTimes % 2 == 0)) // Even
		{
			bStopBlinking = 1;
		}
		break;

	case LED_NO_LINK_BLINK:
		//Revised miniCard Ad-hoc mode "Slow Blink" by Isaiah 2006-08-03	
		//if( (priv->mAssoc || priv->mIbss) ) // Linked.
		if( priv->mAssoc) 
		{
			bStopBlinking = 1;
		}
		else if(priv->mIbss && priv->bMediaConnect )
		{
			bStopBlinking = 1;
		}
		break;
*/
	default:
		bStopBlinking = 1;
		break;
	}

	if(bStopBlinking)
	{
/*
		if( priv->eRFPowerState != eRfOn )
		{
			SwLedOff(dev, pLed);
		}
		else if( priv->bMediaConnect == 1 && pLed->bLedOn == 0)
		{
			SwLedOn(dev, pLed);
		}
		else if( priv->bMediaConnect == 0 &&  pLed->bLedOn == 1)
		{
			SwLedOff(dev, pLed);
		}
*/
		pLed->BlinkTimes = 0;
		pLed->bLedBlinkInProgress = 0;	
	}
	else
	{
		// Assign LED state to toggle.
		if( pLed->BlinkingLedState == LED_ON ) 
			pLed->BlinkingLedState = LED_OFF;
		else 
			pLed->BlinkingLedState = LED_ON;

		// Schedule a timer to toggle LED state. 
		switch( pLed->CurrLedState )
		{
		case LED_BLINK_NORMAL:
			pLed->BlinkTimer.expires = jiffies + LED_BLINK_NORMAL_INTERVAL;
			add_timer(&(pLed->BlinkTimer));			
			//PlatformSetTimer(dev, &(pLed->BlinkTimer), LED_BLINK_NORMAL_INTERVAL);
			break;

		case LED_BLINK_SLOWLY:
			pLed->BlinkTimer.expires = jiffies + LED_BLINK_SLOWLY_INTERVAL;
			add_timer(&(pLed->BlinkTimer));			
			//PlatformSetTimer(dev, &(pLed->BlinkTimer), LED_BLINK_SLOWLY_INTERVAL);
			break;

		case LED_SCAN_BLINK:
		case LED_NO_LINK_BLINK:
			if( pLed->bLedOn ) {
				pLed->BlinkTimer.expires = jiffies + LED_CM2_BLINK_ON_INTERVAL;
				add_timer(&(pLed->BlinkTimer));				
				//PlatformSetTimer(dev, &(pLed->BlinkTimer), LED_CM2_BLINK_ON_INTERVAL);
			} else {
				pLed->BlinkTimer.expires = jiffies + LED_CM2_BLINK_OFF_INTERVAL;
				add_timer(&(pLed->BlinkTimer));		
				//PlatformSetTimer(dev, &(pLed->BlinkTimer), LED_CM2_BLINK_OFF_INTERVAL);
			}
			break;

		default:
			//RT_ASSERT(0, ("SwLedCm2Blink(): unexpected state!\n"));
			pLed->BlinkTimer.expires = jiffies + LED_BLINK_SLOWLY_INTERVAL;
			add_timer(&(pLed->BlinkTimer));
			//PlatformSetTimer(dev, &(pLed->BlinkTimer), LED_BLINK_SLOWLY_INTERVAL);
			break;
		}
	}
}

void
SwLedOn(
	struct net_device *dev, 
	PLED_8187			pLed
)
{
	struct r8180_priv *priv = ieee80211_priv(dev);

	switch(pLed->LedPin)
	{
	case LED_PIN_GPIO0:
		write_nic_byte(dev,0xFF91,0x01);
		write_nic_byte(dev,0xFF90,0x00);	// write 0 : LED on
		break;

	case LED_PIN_LED0:
		priv->PsrValue &= ~(0x01 << 4);
		write_nic_byte(dev, PSR, priv->PsrValue);
		break;

	case LED_PIN_LED1:
		priv->PsrValue &= ~(0x01 << 5);
		write_nic_byte(dev, PSR, priv->PsrValue);
		break;

	default:
		break;
	}

	pLed->bLedOn = 1;
}

void
SwLedOff(
	struct net_device *dev, 
	PLED_8187			pLed
)
{
	struct r8180_priv *priv = ieee80211_priv(dev);

	switch(pLed->LedPin)
	{
	case LED_PIN_GPIO0:
		write_nic_byte(dev,0xFF91,0x01);
		write_nic_byte(dev,0xFF90,0x01);	// write 1 : LED off
		break;

	case LED_PIN_LED0:
		priv->PsrValue |= (0x01 << 4);
		write_nic_byte(dev, PSR, priv->PsrValue);
		break;

	case LED_PIN_LED1:
		priv->PsrValue |= (0x01 << 5);
		write_nic_byte(dev, PSR, priv->PsrValue);
		break;

	default:
		break;
	}

	pLed->bLedOn = 0;
}	

