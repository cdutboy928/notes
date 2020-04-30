### AWS EC2
#### how to choose instances
!!!Instances suitable for Hashcat
##### [P2 Instance Details](https://amazonaws-china.com/ec2/instance-types/p2/)

Name|GPUs|vGPUs|RAM|Network Brandwidth|Benchmark for WPA!!!
--|--|--|--|--
p2.xlarge|1|4|61|High
p2.8xlarge|8|32|488|10Gbps
p2.16xlarge|16|64|732|20Gbps

##### [p3 Instance Details](https://amazonaws-china.com/ec2/instance-types/p3/)

Instance Size|GPUs(Tesla V100)|GPU Peer to Peer|GPU Memory(GB)|vGPUs|Memory(GB)|Network Bandwidth|Benchmark for WPA!!!
p3.2xlarge|1|N/A|16|8|61|Up to 10 Gbps
p3.8xlarge|4|NVLink|64|32|244|10 Gbps
p3.16xlarge|8|NVLink|128|64|488|25Gbps
##### [how to run a free AWS Instance](https://aws.amazon.com/free/)
#### ways to pay
It's on demand meaning that you can turn it on and off as you need it. It's scalable meaning that if you want to have more than one machine and they have the machines available you can purchases the services of additional machine. So if you want to crack passwords ten times fast you could fire up 10 servers.
There are four ways to pay for Amazon EC2 instances: On-Demond, Spot Instances,Reserved Instances, and Dedicated Hosts.
##### About reboot
The shutdown behavior is pretty interesting because you can specify that automatically when you build the server. If you shut it down or the server shuts down unexpectedly it's either going to shutdown or terminate. If you shutdown the machine you can restart it at a future point and however you had it configured and whatever data stored on it will still be there. So it's persistent between shutdowns and startups. But if you terminate a machine the data is all going to be gone. So you don't want to terminate a machine if you expect you're going to want to utilize the software on it or the data on it in the future.
###### Reboot Your Instance
An instance reboot is equivalent to an operating system reboot. In most cases, it takes only a few minutes to reboot your instance. When you reboot an instance, it remains on the same physical host, so your instance keeps it public DNS name (IPv4), private IPv4 address, IPv6 address (if applicable), and any data on its instance store volumes.
Rebooting an instance doesn't start a new instance billing period (with a minimum one-minute charge), unlike stopping and restarting your instance.
We might schedule your instance for a reboot for necessary maintenance, such as to apply updates that require a reboot. No action is required on your part; we recommend that you wait for the reboot to occur within its scheduled window. For more information, see Scheduled Events for Your Instances.
We recommend that you use the Amazon EC2 console, a command line tool, or the Amazon EC2 API to reboot your instance instead of running the operating system reboot command from your instance. If you use the Amazon EC2 console, a command line tool, or the Amazon EC2 API to reboot your instance, we perform a hard reboot if the instance does not cleanly shut down within four minutes. If you use AWS CloudTrail, then using Amazon EC2 to reboot your instance also creates an API record of when your instance was rebooted.
* To reboot an instance using the console
    1. Open the Amazon EC2 console.
    2. In the navigation pane, choose **Instances**.
    3. Select the instance and choose **Actions**, **Instance State**, **Reboot**.
    4. Choose **Yes**, **Reboot** when prompted for confirmation.
* To reboot an instance using the command line
    You can use one of the following commands. For more information about these command line interfaces, see Accessing Amazon EC2.
    * reboot-instances (AWS CLI)
    * Restart-EC2Instance (AWS Tools for Windows PowerShell)
##### [Amazon EC2 Spot Instances Pricing](https://amazonaws-china.com/ec2/spot/pricing/)
With Spot instances, You pay the Spot price that's in effect for the time period your instances are running. Spot instance prices are set by Amazon EC2 and adjust gradually based on long-term trends in supply and demand for Spot instance capacity. The following table displays the Spot price for each region and instance type (updated every 5 minutes).
Spot instances are available at a discount of up to 90% off compared to On-Demand pricing. To compare the current Spot prices against standard On-Demand rates, visit the [Spot Instance Advisor](https://amazonaws-china.com/ec2/spot/instance-advisor/) and [Simple Monthly Calculator](https://calculator.s3.amazonaws.com/index.html)
You can bid on excess capacity that Amazon has and so in this particular case for a GPU box you can see they actually show me in the bottom middle left that it actually costs around 35 cents per hour for their available capacity. I bid 55 cents per hour. They would only charge me with the going rate so if I bid 55 cents and the going rate is 35 then they only charge m 35 cents .
Spot instances are also available to run for a predefined duration-in hourly increments up to six hours in length-at a discount of up to 30-50% compared to On-Demand pricing.

GPU Instances-Current Generation|Linux/UNIX Usage|Windows Usage
g2.2xlarge|N/A*|N/A*
g2.8xlarge|N/A*|N/A*
g3.4xlarge|$0.342 per Hour|$1.078 per Hour
g3.8xlarge|$0.684 per Hour|$2.156 per Hour
g3.16xlarge|$2.5154 per Hour|$5.3877 per Hour
p2.xlarge|$0.27 per Hour|$0.454 per Hour
p2.8xlarge|$2.16 per Hour|$3.632 per Hour
p2.16xlarge|$14.4 per Hour|$17.344 per Hour
p3.2xlarge|$1.0555 per Hour|$1.286 per Hour
p3.8xlarge|$4.2244 per Hour|$5.144 per Hour
p3.16xlarge|$7.344 per Hour|$10.288 per Hour
###### Amazon EC2 Spot Can Now Stop and Start Your Spot Instances
Amazon EC2 Spot now allows Amazon EBS-backed instances to be stopped in the event of interruption, instead of being terminated when capacity is no longer available at your preferred price. Spot can then fulfill your request by restarting instances from a stopped state when capacity is available within your price and time requirements. To use this new feature, choose "stop" instead of "terminate" as the interruption behavior when submitting a persistent Spot request. When you choose "stop", Spot will shut down your instance upon interruption. The EBS root device and attached EBS volumes are saved, and their data persists. When capacity is available again within your price and time requirements, Spot will restart your instance. Upon restart, the EBS root device is restored from its prior state, previously attached data volumes are reattached, and the instance retains its instance ID.
This feature is available for persistent Spot requests and Spot Fleets with the "maintain" fleet option enabled. You will not be charged for instance usage while your instance is stopped. EBS volume storage is charged at standard rates. You can cancel your bid at any time to terminate stopped instances. This feature is only available for instances with an Amazon EBS volume as their root device.
###### how to request and launch a Spot Instance
[how to request and launch a Spot Instance](./aws/'Spot Instance How to Run Spot Instance On AWS AWS Spot Instance Tutorial Save Cost Using Spot.mp4')
[how to request and launch a Spot Instance](https://www.youtube.com/watch?v=eWw5C8ucacY)
Spot Instances can be requested using the AWS Management Console or Amazon EC2 APIs. To start with the AWS Management Console simply:
1. Log in to the AWS Management Console, then click the "Amazon EC2" tab.
2. Click on "Spot Requests" in the navigation pane on the left.
3. Click on "Pricing History" to open a view of historical pricing selectable by instance type. This will help you choose a maximum price for your request. Pricing shown is specific to the Availability Zone selected. If no Availability Zone is selected, you will see the prices or each Availability Zone in the Region.
4. Click on "Request Spot Instances" and proceed through the Launch Instance Wizard process, choosing an AMI(stands for Amazon Machine Image) and instance type. Enter the number of Spot Instances you would like to request, your maximum price and whether the request is persistent or not. After choosing your key pair and security group(s), you are ready to submit your Spot Instance request.
So basically you have your on-demand instances which keeps on running and you have to pay the hourly charges for it. Spot Instances are those instances, for example, AWS have certain amount of hardware which is available 24/7 and which is not in use actually. So AWS offers to use those hardwares and computer sources on a very cheaper price. So what happens is that there could be a resource available so you can place your bid that you want certain type of instance at a particular price. Say for example, you want c3.large instance at the price of say 0.05 $/hour, the price for this type of instance of on-demand is 0.105 $/hour. So you can bid at a particular rate or maybe the best possible minimum rate in the market and you can if the hardware is available then you can get that instance up and running. So this is how you pay less for the same computer source. And in case that somebody else requires that hardware at the price say 0.43 $/hour and if AWS don't have another resource available then it will terminate yours and it will give it to someone else then in that case your instance will get terminated. So this is how the Spot Instance works.
* Here you can specify what kind of request type is:
  * **Request**: The simple request type, which submits a one-time Spot instance request.
  * **Request and Maintain**: Request a fleet of Spot instances to maintain your target capacity. If you want to maintain a certain number of instances you can choose this one.
  * **Reserve for duration**: Request a Spot instance with no interruption for 1 to 6 hours (a spot block). 
* About Maximum price:
Here you can bid your price or maybe you can use the automated bidding so it will automatically place the bidding on behalf of you (Provision Spot instances at the current Spot price capped at the On-Demand price) which is as lowest at possible.
* User data!!!how to write and run a script!!!
    If you want to specify user data such as certain scripts or certain commands that should be executed on the launch of instance you can specify here.
* Keypair
    You can create a new keypair or use a created keypair.
    Create a new keypair and save to local drive, and connect to the instance using the follow command via SSH:
    `ssh -i path/to/pem/file ec2-user@14.169.42.132`
    The ip address can be checked from "Instances" on the AWS control pane.

###### Spot Request Status
To help you track your Spot Instance requests and plan your use of Spot Instances, use the request status provided by Amazon EC2. For example, the request status can provide the reason why your Spot request isn't fulfilled yet, or list the constraints that are preventing the fulfillment of your Spot request.
At each step of the process-also called the Spot request *lifecycle*, specific events determine successive request states.
* Life Cycle of a Spot Request
    The following diagram shows you the paths that your Spot request can follow throughout its lifecycle, from submission to termination. Each step is depicted as a node, and the status code for each node describes the status of the Spot request and Spot Instance.
    ![lifecycle of a Spot Request](spot-bid-status-diagram.png)
    * Pending evaluation
        As soon as you make a Spot Instance request, it goes into the `pending-evaluation` state unless one or more request parameters is not valid `bad-parameters`).

Status Code|Request State|Instance State
--|--|--
pending-evaluation|open|n/a
bad-parameters|closed|n/a
    * Holding
        If one or more request constrains are valid but can't be met yet, or if there is not enough capacity, the request goes into a holding state waiting for the constraints to be met. The request options affect the likelihood of the request being fulfilled. For example, if you specify a maximum price below the current Spot price, your request stays in a holding state until the Spot price goes below your maximum price. If you specify an Availability Zone group, the request stays in a holding state until the Availability Zone constraint is met.

Status Code|Request State|Instance State
--|--|--
capacity-not-available|open|n/a
capacity-oversubscribed|open|n/a
price-too-low|open|n/a
not-scheduled-yet|open|n/a
launch-group-constraint|open|n/a
az-group-constraint|open|n/a
placement-group-constraint|open|n/a
constraint-not-fulfillable|open|n/a
    * Pending evaluation/fulfillment-terminal
        Your Spot Instance request can go to a terminal state if you create a request that is valid only during a specific time period and this time period expires before your request reaches the pending fulfillment phase, you cancel the request, or a system error occurs.

Status Code|Request State|Instance State
--|--|--
schedule-expired|cancelled|n/a
cancelled-before-fulfillment*|cancelled|n/a
bad-parameters|failed|n/a
system-error|closed|n/a
`*`: If you cancel the request.
    * Pending fulfillment
        When the constraints you specified (if any) are met and your maximum price is equal to or higher than the current Spot price, your Spot request goes into the pending-fulfillment state.
        At this point, Amazon EC2 is getting ready to provision the instances that you requested. If the process stops at this point, it is likely to be because it was cancelled by the user before a Spot Instance was launched, or because an unexpected system error occurred.

Status Code|Request State|Instance State
--|--|--
pending-fulfillment|open|n/a
    * Fulfilled
        When all the specifications for your Spot Instances are met, your Spot request is fulfilled. Amazon EC2 launches the Spot Instances, which can take a few minutes. If a Spot Instance is hibernated or stopped when interrupted, it remains in this state until the request can be fulfilled again or the request is cancelled.

Status Code|Request State|Instance State
--|--|--
fulfilled|active|pending→ running
fulfilled|active|stopped→ running
    * Fulfilled-terminal
        Your Spot Instances continue to run as long as your maximum price is at or above the Spot price, there is available capacity for your instance type, and you don't terminate the instance. If a change in the Spot price or available capacity requires Amazon EC2 to terminate your Spot Instances, the Spot request goes into a terminal state. For example, if your price equals the Spot price but Spot Instances are not available, the status code is `instance-terminated-capacity-oversubscribed`. A request also goes into the terminal state if you cancel the Spot request or terminate the Spot Instances.

Status Code|Request State|Instance State
--|--|--
request-cancelled-and-instance-running|cancelled|running
marked-for-stop|active|running
marked-for-termination|closed|running
instance-stopped-by-price|disabled|stopped
instance-stopped-by-user|disabled|stopped
instance-stopped-capacity-oversubscribed|disabled|stopped
instance-stopped-no-capacity|disabled|stopped
instance-terminated-by-price|closed(one-time), open(persistent)|terminated
instance-terminated-by-schedule|closed|terminated
instance-terminated-by-service|cancelled|terminated
instance-terminated-by-user †|closed or cancelled*|terminated
instance-terminated-no-capacity|closed(one-time), open(persistent)|terminated
instance-terminated-capacity-oversubscribed|closed(one-time), open(persistent)|terminated
instance-terminated-launch-group-constraint|closed(one-time), open(persistent)|terminated
`†`: A Spot Instance can only get to this state if a user runs the shutdown command from the instance. We do not recommend that you do this, as the Spot service might restart the instance.
`*`: The request state is closed if you terminate the instance but do not cancel the request. The request state is cancelled if you terminate the instance and cancel the request. Note that even if you terminate a Spot Instance before you cancel its request, there might be a delay before Amazon EC2 detects that your Spot Instance was terminated. In this case, the request state can either be closed or cancelled.
    * Persistent requests
        When your Spot Instances are terminated (either by you or Amazon EC2), if the Spot request is a persistent request, it returns to the pending-evaluation state, and then Amazon EC2 can launch a new Spot Instance when the constraints are met.
* Getting Request Status Information
    You can get request status information using the AWS Management Console or a command line tool.
    * To get request status information using the console
        1. Open the Amazon EC2 console at https://console/aws.amazon.com/ec2/ .
        2. In the navigation pane, choose **Spot Requests**, and then select the Spot Request.
        3. Check the value of Status in the Description tab.
* Spot Request Status Codes
    Spot request status information is composed of a status code, the update time, and a status message. Together, these help you determine the disposition of your Spot request.
    The following are the Spot request status codes:
    * `az-group-constraint`: Amazon EC2 cannot launch all the instances you requested in the same Availability Zone.
    * `bad-parameters`: One or more parameters for your Spot request are not valid (for example, the AmI you specified does not exist). The status message indicates which parameter is not valid.
    * `cancelled-before-fulfillment`: The user cancelled the Spot request before it was fulfilled.
    * `capacity-not-available`: There is not enough capacity available for the instances that you request.
    * `capacity-oversubscribed`: There is not enough capacity available for the instances that you requested.
    * `constraint-not-fulfillable`: The Spot request can't be fulfilled because one or more constraints are not valid (for example, the Availability Zone does not exist). The status message indicates which constraint is not valid.
    * `fulfilled`: The Spot request is active, and Amazon EC2 is launching your Spot Instances.
    * `instance-stopped-by-price`: Your instance was stopped because the Spot price exceeded your maximum price.
    * `instance-stopped-by-user`: Your instance was stopped because a user ran `shutdown -h` from the instance.
    * `instance-stopped-capacity-oversubscribed`: Your instance was stopped because the number of Spot requests with maximum prices equal to or higher than the Spot price exceeded the available capacity in this Spot Instance pool. (Note that the Spot price might not have changed.)
    * `instance-stopped-no-capacity`: Your instance was stopped because there was no longer enough Spot capacity available for the instance.
    * `instance-terminated-by-price`: Your instance was terminated because the Spot price exceeded your maximum price. If your request is persistent, the process restarts, so your request is pending evaluation.
    * `instance-termianted-by-schedule`: Your Spot Instance was terminated at the end of its scheduled duration.
    * `instance-terminated-by-service`: Your instance was terminated from a stopped state.
    * `instance-terminated-by-user` or `spot-instance-terminated-by-user`: You terminated a Spot Instance that had been fulfilled, so the request state is closed (unless it's persistent request) and the instance state is terminated.
    * `inxtance-terminated-capacity-oversubscribed`: Your instance was terminated because the number of Spot requests with maximum prices equal to or higher than the Spot price exceeded the available capacity in this Spot Instance pool. (Note that the Spot price might not have changed.)
    * `instance-terminated-launch-group-constraint`: One or more of the instances in your launch group was terminated, so the launch group constraint is no longer fulfilled.
    * `instance-terminated-no-capacity`: Your instance was terminated because there is no longer enough Spot capacity available for the instance.
    * `launch-group-constraint`: Amazon EC2 cannot launch all the instances that you requested at the same time. All instances in a launch group are started and terminated together.
    * `limit-exceeded`: The limit on the number of EBS volumes or total volume storage was exceeded.
    * `markded-for-stop`: The Spot Instance is marked for stopping.
    * `marked-for-termination`: The Spot Instance is marked for termination.
    * `not-scheduled-yet`: The Spot request will not be evaluated until the scheduled date.
    * `pending-evaluation`: After yo make a Spot Instance request, it goes into the pending-evaluation state while the system evaluates the parameters of your request.
    * `pending-fulfillemnt`: Amazon EC2 is trying to provision your Spot Instances.
    * `placement-group-constraint`: The Spot request can't be fulfilled yet because a Spot Instance can't be added to the placement group at this time.
    * `price-too-low`: The request can't be fulfilled yet because your maximum price is below the Spot price. In this case, no instance is launched and your request remains open.
    * `request-cancelled-and-instance-running`: You cancelled the Spot request while the Spot Instances are still running. The request is cancelled, but the instances remain running.
    * `schedule-expired`: The Spot request expired because it was not fulfilled before the specified date.
    * `system-error`: There was an unexpected system error. If this is a recurring issue, please contact customer support for assistance.
##### [Amazon EC2 On-Demand Instances Pricing](https://amazonaws-china.com/ec2/pricing/on-demand/)
On-Demand isntances let you pay for compute capacity by the hour or second (minimum of 60 seconds) with no long-term commitments. This frees you from the costs and complexities of planning, purchasing, and maintaining hardware and transforms what are commonly large fixed costs into much smaller variable costs.

GPU Instances - Current Generation|vCPU|ECU|Memory(GiB)|Instance Storage(GB)|Linux/UNIX Usage
--|--|--|--|--|--
p3.2xlarge|8|26|61GB|EBS Only|$3.06 per Hour
p3.8xlarge|32|94|244GiB|EBS Only|$12.24 per Hour
p3.16xlarge|64|188|488 GiB|EBS Only|$24.48 per Hour
p2.xlarge|4|12|61 GiB|EBS Only|$0.90 per Hour
p2.8xlarge|32|94|488 GiB|EBS Only|$7.20 per Hour
p2.16xlarge|64|188|768 GiB|EBS Only|$14.40 per Hour
g3.4xlarge|16|47|122 GiB|EBS Only|$1.14 per Hour
g3.8xlarge|32|94|244 GiB|EBS Only|$2.28 per Hour
g3.16xlarge|64|188|488 GiB|EBS Only|$4.56 per Hour

They charge you by the fractional rounding up so if you run it for one minute you're going to pay for an hour; if you run it for an hour in one minute you're going to pay for two hours.

###### how to start a On-Demand Instance

#### AWS User data and custom scripts!!!

#### ASW command line!!!
The AWS Command Line Interface (CLI) is a unified tool to mange your AWS services. With just one tool to download and configure, you can control multiple AWS services from the command line and automate them through scripts.
The AWS CLI introduces a new set of simple file commands for efficient file transfers to and from Amazon S3.
##### aws-shell (Developer Preview)
aws-shell is a command-lien shell program that provides convenience and productivity features to help both new and advanced users of the AWS Command Line Interface. Key features include the following.
* Fuzzy auto-completion for
    * Commands (e.g. ec2, describe-instances, sqs, create-queue)
    * Options (e.g. `--instance-ids`, `--queue-url`)
    * Resource identifiers (e.g. Amazon EC2 instance IDs, Amazon SQS queue URLs, Amazon SNS topic names)
* Dynamic in-line documentation
    * Documentation for commands and options are displayed as you type
* Execution of OS shell commands
    * Use common OS commands such as cat, ls, and cp and pipe inputs and outputs without leaving the shell
    * Execute regular shell commands by piping or prefixing shell commands with `!`.
* Export executed commands to a text editor
    Running the `.edit` command after executing some commands gives you all the commands in your default text editor.
##### Installing
The AWS Command Line Interface User Guide walks you through installing and configuring the tool. After that, you can begin making calls to your AWS services from the command line.
###### What is the AWS Command Line Interface?
The AWS CLI is an open source tool built on top of the AWS SDK for Python (Boto) that provides commands for interacting with AWS services. With minimal configuration, you can start using all of the functionality provided by the AWS Management Console from your favorite terminal program.
* Linux shells-Use common shell programs such as Bash, Zsh, and tsch to run commands in Linux, macOS, or Unix.
* Windows command line-On Microsoft Windows, run commands in either PowerShell or the Windows Command Processor.
* Remotely-Run commands on Amazon EC2 instances through a remote terminal such as PuTTY or SSH, or with Amazon EC2 systems manager.
The AWS CLI provides direct access to AWS services' public APIs. Explore a service's capabilities with the AWS CLI, and develop shell scripts to manage your resources. Or take what you've learned to develop programs in other languages with the AWS SDK.
In addition to the low level, API equivalent commands, the AWS CLI also provides customizations for several services. Customizations are higher level commands that simplify using a service with a complex API. For example, the `aws s3` set of commands provide a familiar syntax for managing files in Amazon S3.
**Example Upload a file to Amazon S3**
`aws s3 cp` provides a shell-like copy command, and automatically performs a multipart upload to transfer large files quickly and resiliently.
`~$ aws s3 cp myvideo.mp4 s3://mybucket/`
Performing the same task with the low level commands (available under `aws s3api`) would take a lot more effort.
Depending on your use case, you may want to use the AWS SDK, a toolkit, or the AWS Tools for Windows PowerShell.
* AWS Tools for Windows PowerShell
* AWS SDK for Java
* AWS SDK for .NET
* AWS SDK for JavaScript
* AWS SDK for Ruby
* AWS SDK for Python (Boto)
* AWS SDK for PHP
* AWS SDK for Go
* AWS Toolkit for Eclipse
* AWS Toolkit for Visual Studio
* AWS Mobile SDK for iOS
* AWS Mobile SDK for Android
You can also view-and fork-the source code for the AWS CLI on GitHub in the aws-cli repository.
####### Using the Examples in this Guide
The examples in this guide are formatted with the following conventions:
* Prompt-The command prompt is displayed as a dollar sign (`$`). Do not include the prompt when you type commands.
* Directory-When commands must be executed from a specific directory, the directory name is shown before the prompt symbol.
* User Input-Command text that you should enter at the command lien is formatted as **user input**.
* Replacable Text-Variable text, including names of resources that you choose, or IDs generated by AWS services that you must include in commands, is formatted as *replacable text* (in red color). In multiple line commands or commands where specific keyboard input is required, keyboard commands can also be shown as replacable text.
* Output-Output returned by AWS services is shown beneath user input without any special formatting.
For example, the following command includes user input, replacable text, and output:
![example of aws cli](aws_cli_examples.jpg)
To use this example, type `aws configure` at the command line and press **Enter**. `aws configure` is the command. This command is interactive, so the AWS CLI outputs line of texts, prompting you to enter additional information. Enter each of your access keys in turn and press **Enter**. Then, enter a region name in the format shown, press **Enter**, and press **Enter** a final time to skip the output format setting. The final **Enter** command is shown as replacable text because there is no user input for that line. Otherwise, it would be implied.
The following example shows a simple non-interactive command with output from the service in JSON format:

        $ aws ec2 create-security-group --group-name my-sg --description "My security group"
        {
          "GroupId":"sg-903004f8"
        }
To use this example, enter the full text of the command and press Enter. The name of the security group, `my-sg` is replacable. In this case, you can use the group name as shown, but you will probably want to use a more descriptive name.
The JSON document, including the curly braces, is output. If you configure your CLI to output in test or table format, the output will be formatted differently. JSON is the default output format.
###### Installing the AWS Command Line Interface
The primary distribution method for the AWS CLI on Linux, Windows, and macOS is pip, a package manager for Python that provides an easy way to install, upgrade, and remove Python packages and their dependencies.
* Requirements
    * Python 2 version 2.6.5+ or Python 3 version 3.3+
    * Windows, Linux, macOS, or Unix
If you already have pip and a supported version of Python, you can install the AWS CLI with the following command:
`$ pip install awscli --upgrade --user`
The `--upgrade` option tells pip to upgrade any requirements that are already installed. The `--user` option tells pip to install the program to a subdirectory of your user directory to avoid modifying libraries used by your operating system.
If you encounter issues when you attempt to install the AWS CLI with pip, you can [install the AWS ClI in a virtual environment](https://docs.aws.amazon.com/cli/latest/userguide/awscli-install-virtualenv.html) to isolate the tool and its dependencies, or use a different version of Python than you normally do.
####### Standalone Installers
For offline or automated installations on Linux, macOS, or Unix, try the [bundled installer](https://docs.aws.amazon.com/cli/latest/userguide/awscli-install-bundle.html). The bundled installer includes the AWS CLI, its dependencies, and a shell script that performs the installation for you.
On windows, you can also use the [MSI installer](https://docs.aws.amazon.com/cli/latest/userguide/awscli-install-windows.html#install-msi-on-windows). Both of these methods simplify the initial installation, with the tradeoff of being more difficult to upgrade when a new version of the AWS CLI is released.
After you install the AWS CLI, you may need to add the path to the executable file to your PATH variable. For platform specific instructions, see the following topics:
* Linux-[Adding the AWS CLI Executable to your Command Line Path](https://docs.aws.amazon.com/cli/latest/userguide/awscli-install-linux.html#awscli-install-linux-path)
* Windows-[Adding the AWS CLI Executable to your Command Line Path](https://docs.aws.amazon.com/cli/latest/userguide/awscli-install-windows.html#awscli-install-windows-path)
* macOS-[Adding the AWS CLI Executable to your Command Line Path](https://docs.aws.amazon.com/cli/latest/userguide/awscli-install-windows.html#awscli-install-windows-path)
Verify that the AWS CLI installed correctly by running `aws --version`.
`$ aws --version`
`aws-cli/1.11.84 Python/3.6.2 Linux/4.4.0-59-generic botocore/1.5.47`
The AWS CLI is updated regularly to add support for new services and commands. To update to the latest version of the AWS CLI, run the installation command again.
`$ pip isntall swscli --update --user`
If you need to uninstall the AWS CLI, use pip uninstall.
`pip uninstall awscli`
##### Configuring the AWS CLI
This section explains how to configure settings that the AWS Command Line Interface uses when interacting with AWS, such as your security credentials and the default region.
**Note**: The AWS CLI signs requests on your behalf, and includes a date in the signature. Ensure that your computer's date and time are set correctly; if not, the date in the signature may not match the date of the request, and AWS rejects the request.
###### Quick Configuration
For general use, the `aws configure` command is the fastest way to set up your AWS CLI installation.

        $ aws configure
        AWS Access Key ID [None]: AKIAIOSFODNN7EXAMPLE
        AWS Secret Access Key [None]: wJalrXUtnFEMI/K7MDENG/bPxRfiCYEXAMPLEKEY
        Default region name [None]: us-west-2
        Default output format [None]:json
The AWS CLI will prompt you for four pieces of information. AWS Access Key ID and AWS Secret Access Key are your account credentials.
**To get the access key ID and secret access key for an IAM user**
Access keys consist of an access key ID and secret access key, which are used to sign programmatic requests that you make to AWS. If you don't have access keys, you can create them from the AWS Management Console. We recommend that you use IAM access keys instead of AWS account root user access keys. IAM lets you securely control access to AWS services and resources in your AWS account.
The only time that you can view or download the secret access keys is when you create the keys. You cannot recover them later. However, you can create new access keys at any time. You must also have permissions to perform the required IAM actions. For more information, see Permissions Required to Access IAM Resources in the IAM User Guide.
1. Open the IAM console.
2. In the navigation pane of the condole, choose **Users**.
3. Choose your IAM user name (not the check box).
4. Choose the Security credentials tab and then choose **Create access key**.
5. To see the new access key, choose **Show**. Your credentials will look something like this:
  * Access key ID: AKIAIOSFODNN7EXAMPLE
  * Secret access key: wJalrXUtnFEMI/K7MDENG/bPxRfiCYEXAMPLEKEY (different from the key pair used to launch and connect to an instance)
6. To download the key pair, choose **Download .csv file**. Store the keys in a secure location.
Keep the keys confidential in order to protect your AWS account, and never email them. Do not share them outside your organization, even if an inquiry appears to come from AWS or Amazon.com. No one who legitimately represents Amazon will ever ask you for your secret key.
Default region is the name of the region you want to make calls against by default. This is usually the region closest to you, but it can be any region. For example, type `us-west-2` to use US West (Oregon).
**Note**: You must specify an AWS region when using the AWS CLI. For a list of services and available regions, see Regions and Endpoints. The region designators used by the AWS CLI are the same names that you see AWS Management Console URLs and service endpoints.
Default output format can be either json, text, or table. If you don't specify an output format, json is used.
If you have multiple profiles, you can configure additional, named profiles by using the `--profile` option.

        $ aws configure --profile user2
        AWS Access Key ID [None]: AKIAI44QH8DHBEXAMPLE
        AWS Secret Access Key [None]: je7MtGbClwBF/2Zp9Utk/h3yCo8nvbEXAMPLEKEY
        Default regioon name [None]: us-east-1
        Default output format [None]: text
To update any of your settings, simply run `aws configur` again and enter new values as appropriate. The next sections contain more information on the files that `aws configure` creates, additional settings, and named profiles.
###### Configuration and Credential Files
####### Configuration Settings and Precedence
The AWS CLI uses a *provider chain* to look for AWS credentials in a number of different places, including system or user environment variables and local AWS configuration files.
The AWS CLI looks for credentials and configuration settings in the following order:
1. Command line options-region, output format and profile can be specified as command options to override default settings.
2. Environment variables-AWS_ACCESS_KEY_ID, AWS_SECRET_ACCESS_KEY, and AWS_SESSION_TOKEN.
3. The AWS credential file-located at `~/.aws/credentials` on Linux, macOS, or Unix, or at `C:\Users\Username\.aws\credentials` on Windows. This file can contain multiple named profiles in addition to a default profile.
4. The CLI configuration file-typically located at `~/.aws/config` on Linux, macOS, or Unix, or at `C:\Users\USERNAME\.aws\config` on Windows. This file can contain a default profile, named profiles, and CLI specific configuration parameters for each.
5. Container credentials-provided by Amazon Elastic Container Service on container instances when you assign a role to your task.
6. Instance profile credentials-these credentials can be used on EC2 instances with an assigned instance role, and are delivered through the Amazon EC2 metadata service.
####### Configuration and Credential Files
The CLI stores credentials specified with `aws configure` in a local file named `credentials` in a folder named `.aws` in your home directory. Home directory location varies but can be referred to using the environment variables `%UserProfile%` in Windows and `$HOME` or `~`(tilde) in Unix-like systems.
For example, the following commands list the contents of the `.aws` folder:
* Linux, macOS, or Unix
    `$ ls ~/.aws`
* Windows
    `> dir "%UserProfile%\.aws"`
In order to separate credentials from less sensitive options, region and output format are stored in a separate file named `config` in the same folder.
The default file location for the config file can be overridden by setting the AWS_CONFIG_FILE environment variable to another local path.
**Storing Credentials in Config**
The AWS CLI will also read credentials from the config file. If you want to keep all of your profile settings in a single file, you can. If there are ever credentials in both locations for a profile (say you used `aws configure` to update the profile's keys), the keys in the credentials file will take precedence.
If you use one of the SDKs in addition to the AWS CLI, you may notice additional warnings if credentials are not stored in their own file.
The files generated by the CLI for the profile configured in the previous section look like this:

        cat ~/.aws/credentials
        [default]
        aws_access_key_id=AKIAIOSFODNN7EXAMPLE
        aws_secret_access_key=wJalrXUtnFEMI/K7MDENG/bPxRfiCYEXAMPLEKEY

        cat ~/.aws/config
        [default]
        region=us-west-2
        output=json
The following settings are supported.
**aws_access_key_id**-AWS access key.
**aws_secret_access_key**-AWS secret key.
**aws_session_token**-AWS session token. A session token is only required if you are using temporary security credentials.
**region**-AWS region.
**output**-output format (json, text, or table).
###### Named Profiles
The AWS CLI supports *named profiles* stored in the config and credentials files. You can configure additional profiles by using `aws config` with the `--profile` option or by adding entries to the config and credentials files.
The following example shows a credentials files with two profiles:

        cat ~/.aws/credentials
        [default]
        aws_access_key_id=AKIAIOSFODNN7EXAMPLE
        aws_secret_access_key=wJalrXUtnFEMI/K7MDENG/bPxRfiCYEXAMPLEKEY

        [user2]
        aws_access_key_id=AKIAI44QH8DHBEXAMPLE
        aws_secret_access_key=je7MtGbClwBF/2Zp9Utk/h3yCo8nvbEXAMPLEKEY
Each profile uses different credentials-perhaps from two different IAM users-and can also use different regions and output formats.

        cat ~/.aws/config
        [default]
        region=us-west-2
        output=json

        [profile user2]
        region=us-east-1
        output=text
**Important**: The AWS credentials file uses a different naming format than the CLI config file for named profiles. Do not include the 'profile' prefix when configuring a named profile in the AWS credentials file.
####### Using Profiles with the AWS CLI
To use a named profile, add the `--profile` option to your command. The following example lists running instances using the user2 profile from the previous section.
`$ aws ec2 describe-instances --profile user2`
If you are going to use a named profile for multiple commands, you can avoid specifying the profile in every command by setting the AWS_PROFILE environment variable at the command line.
* Linux, macOS, or Unix
    `$ export AWS_PROFILE=user2`
* Windows
    `>set AWS_PROFILE=user2`
Setting the environment variable changes the default profile until the end of your shell session, or until you set the variable to a different value. More on variables in the next section.
###### Environment Variables
Environment variables override configuration and credential files and can be useful for scripting or temporarily setting a named profile as the default.
The AWS CLI supports the following environment variables.
* AWS_ACCESS_KEY_ID-AWS access key.
* AWS_SECRET_ACCESS_KEY-AWS secret key. Access and secret key variables override credentials stored in credential and config files.
* AWS_SESSION_TOKEN-Specify a session token if you are using temporary security credentials.
* AWS_DEFAULT_REGION-AWS region. This variable overrides the default region of the in-use profile, if set.
* AWS_DEFAULT_OUTPUT-Change the AWS CLI's output formatting to json, text, or table.
* AWS_PROFILE-name of the CLI profile to use. This can be the name of a profile stored in a credential or config file, or default to use the default profile.
* AWS_CA_BUNDLE-Specify the path to a certificate bundle to use for HTTPS certificate validation.
* AWS_SHARED_CREDENTIALS_FILE-Change the location of the file that the AWS CLI uses to store access keys.
* AWS_CONFIG_FILE-Change the location of the file that the AWS CLI uses to store configuration profiles.
The following example shows how you would configure environment variables for the default user from earlier in this guide.
* Linux, macOS, or Unix
    `$ export AWS_ACCESS_KEY_ID=AKIAIOSFODNN7EXAMPLE`
    `$ export AWS_SECRET_ACCESS_KEY=wJalrXUtnFEMI/K7MDENG/bPxRfiCYEXAMPLEKEY`
    `$ export AWS_DEFAULT_REGION=us-west-2`
* Windows
    `> set AWS_ACCESS_KEY_ID=AKIAIOSFODNN7EXAMPLE`
    `> set AWS_SECRET_ACCESS_KEY=wJalrXUtnFEMI/K7MDENG/bPxRfiCYEXAMPLEKEY`
    `> set AWS_DEFAULT_REGION=us-west-2`
###### Command Line Options
You can use the following command line options to override the default configuration settings for a single command. You cannot use command lien options to specify credentials.
* `--profile`: The name of a named profile to use.
* `--region`: The AWS Region to call.
* `--outptu`: The output format.
* `--endpoint-url`: The URL to make the call against. For most commands, the AWS CLI automatically determines the URL based on the service and AWS Region. However, some commands require that you specify an account-specific URL.
When you provide one of these options at the command line, it overrides the default configuration and corresponding profile setting for a single command. Each option takes a string argument with a space or equals sign (=) separating the argument from the option name. When the argument string contains a space, use quotation marks around the argument.
**Tip**: To set up additional profiles, you can use the `--profile` options with `aws config`.
`$ aws configure --profile <profilename>`
Common uses for command line options include checking your resources in multiple AWS Regions, and changing the output format for legibility or ease of use when scripting. For example, if you're not sure which region your instance is running, you can run the `describe-instances` command against each region until you find it, as follows.

        $ aws ec2 describe-instances --output table --region us-east-1
        ---------------
        |DescribeInstances|
        +-------------+
        $ aws ec2 describe-instances --output table --region us-west-1
        ---------------
        |DescribeInstances|
        +-------------+
        $ aws ec2 describe-instances --output table --region us-west-2
        --------------------------------------
        |           DescribeInstances       |
        +----------------------------------+
        ||          Reservations        ||
        |+--------------------------------+|
        || OwnerId      |01234567890        ||
        || ReservationI  | r-abcdefgh       ||
        |+------------+--------------------+|
        |||         Instances           |||
        ||+-------------+------------------+||
        ||| AmiLaunchIndex      |0          |||
        ||| Architecture | x86_64           |||
###### Instance Metadata
To use the CLI from an EC2 instance, create a role that has access to the resources needed and assign that role to the instance when it is launched. Launch the instance and check to see if the AWS CLI is already installed (it comes pre-installed on Amazon Linux).
Install the AWS CLI if necessary and config a default region to avoid having to specify it in every command. You can set the region using `aws configure` without entering credentials by pressing enter twice to skip the first two prompts:

        $ aws configure
        AWS Access Key ID [None]:ENTER
        AWS Secret Access Key [None]:ENTER
        Default region name [None]: us-west-2
        Default output format [None]: json
The AWS CLI will read credentials from the instance metadata.
###### Using an HTTP Proxy
If you need to access AWS through proxy servers, you should configure the HTTP_PROXY and HTTPS_PROXY environment variables with the IP addresses for your proxy servers.
* Linux, macOS, or Unix
    `$ export HTTP_PROXY=http://a.b.c.d:n`
    `$ export HTTPS_PROXY=http://w.x.y.z:m`
* Windows
    `> set HTTP_PROXY=http://a.b.c.d:n`
    `> set HTTPS_PROXY=http://w.x.y.z:m`
In these examples, `http://a.b.c.d:n` and `http://w.x.y.z:m` are the IP addresses and ports for the HTTP and HTTPS proxies.
####### Autenticating a Proxy
* Linux, macOS, or Unix
    `$ export HTTP_PROXY=http://username:password@a.b.c.d:n`
    `$ export HTTPS_PROXY=http://username:password@w.x.y.z:m`
* Windows
    `> set HTTP_PROXY=http://username:password@a.b.c.d:n`
    `> set HTTPS_PROXY=http://username:password@w.x.y.z:m`
**Note**: The AWS CLI does not support NTLM proxies. If you use an NTLM or Kerberos proxy, you may be able to connect through an authentication proxy like Cntlm.
####### Using a proxy on EC2 Instances
If you configure a proxy on an ec2 instance launched with an IAM role, you should also set the NO_PROXY environment variable with the IP address 169.254.169.254, so that the AWS CLI can access Instance Metadata.
* Linux, macOS, or Unix
    `$ export NO_PROXY=169.254.169.254`
* Windows
    `> set NO_PROXY=169.254.169.254`
###### Assuming a Role
An IAM role is a authorization tool that lets a user gain additional permissions, or get permission to peform actions in a different account.
You can configure the AWS Command Line Interface to use a role by creating a profile for the role in the `~/.aws/config` file. The following example shows a role profile named *marketingadmin* that is assumed by the default profile.

        [profile marketadmin]
        role_arn=arn:aws:iam::123456789012:role/marketingadmin
        source_profile=default
In this case, the default profile is an IAM user with credentials and permission to assume a role named marketingadmin. To access the role, you created a named profile. Instead of configuring this profile with credentials, you specify the ARN of the role and the name of the profile that has access to it.
####### Configuring and Using a Role
When you run commands using the role profile, the AWS CLI uses the source profile's credentials to call AWS Security Token Service and assume the specified role. The source profile must have permission to call `sts:assume-role` against the role, and the role must have a trust relationship with the source profile to allow itself to be assumed.
Create a new role in IAM with the permissions that you want users to assume by following the procedure under Creating a Role to Delegate Permissions to an IAM User in the AWS Identity and Access Management User Guide. If the role and the target IAM user are in the same account, you can enter your own account ID when configuring the role's trust relationship.
After creating the role, modify the trust relationship to allow the IAM user to assume it. The following example shows a trust relationship that allows a trust relationship that allows a role to be assumed by an IAM user named *jonsmith*:

        {
        "Version":"2012-10-17",
        "Statement":[
         {
          "Sid":"",
          "Effect":"Allow",
          "Principal":{
           "AWS":"arn:aws:iam::123456789012:user/jonsmith"
         },
         "Action":"sts:AssumeRole"
         }
         ]
         }
Next, grant your IAM user permission to assume the role. The following example shows an AWS Identity and Access Management policy that allows an IAM user to assume the marketingadmin role:

        {
         "Version":"2012-10-17",
         "Statement":[
          {
           "Effect":"Allow",
           "Action":"sts:AssumeRole",
           "Resource":"arn:aws:iam::123456789012:role/marketingadmin"
           }
          ]
          } 
The user doesn't need to have any additional permissions to run commands using the rule profile. If you want your users to be able to access AWS resources without using the role, apply additional inline or managed policies for those resources.
With the role profile, role permissions, trust relationship and user permissions applied, you can assume the role at the command line by using the `profile` option. For example:
`$ aws s3 ls --profile marketingadmin`
To use the role for multiple calls, you can set the AWS_PROFILE environment variable for the current session from the command line:
* Linux. macOS, or Unix
    `$ export AWS_PROFILE=marketingadmin`
* Windows
    `> set AWS_PROFILE=marketingadmin`
For more information on configuring IAM users and roles, see Users and Groups and Roles in the *AWS Identity and Access Management User Guide*.
####### Using Multifactor Authentication
For additional security, you can require users to provide a one time key generated from a authentication device or mobile app when they attempt to make a call using the role profile.
First, modify the trust relationship on the role to require multifactor authentication:

        {
         "Version":"2012-10-17",
         "Statement":[
          { 
           "Sid":"",
           "Effect":"Allow",
           "principal":{"AWS":"arn:aws:iam::123456789012:user/jonsmith"},
           "Action":"sts:AssumeRole",
           "Condition": { "Bool":{ "aws:MutiFactorAuthPresent":true}}
           }
          ]
          } 
Next, add a line to the role profile that specifies the ARN of the user's MFA device:

        [profile marketingadmin]
        roel_arn=arn:aws:iam::123456789012:role/marketingadmin
        source_profile=default
        mfa_serial=arn:aws:iam::123456789012:mfa/jonsmith
The mfa_serial setting can take an ARN, as show, or the serial number of a hardware MFA token.

####### Cross Account Roles
You can enable IAM users to assume roels that belong to different accounts by configuring the role as a cross account role. During role creating, set the role type to oen of the options under Role for Cross-Account Access and optionally select **Require MFA**. The **Require MFA** option configures the appropriate condition in the trust relationship as described in Using Multifactor Authentication.
If you use an external ID to provide addtional control over who can assume a role across accounts, add an external_id parameter to the role profile:

        [profile crossaccountrole]
        role_arn=:aws:iam::234567890123:role/xaccount
        source_profile=default
        mfa_serial=arn:aws:iam::123456789012:mfa/jonsmith
        external_id=123456
####### Clearing Cached Credentials
When you assume a role, the AWS CLI caches the temporary credentials locally until they expire. If your role's temporary credentials are revoked, you can delete the cache to force the AWS CLI to retrieve new credentials.
* Linux, macOS, or Unix
    `$ rm -r ~/.aws/cache`
* Windows
    `> del /s /q %UserProfile%\.aws\cache`
###### Command Completion
On Unix-like systems, the AWS CLI includes a command-completion feature that enables you to use the **TAB** key to complete a partially typed command. This feature is not automatically installed so you need to configure it manually.
Configuring command completion requires two pieces of information: the name of the shell you are using and the location of the aws_completer script.
**Completion on Amazon Linux**
Command completion is configured by default on instances running Amazon Linux.
####### Identify Your Shell
If you are not sure which shell you are using, identify it with one of the following commands:
* `echo $SHELL`-show the shell's installation directory. This will usually match the in-use shell, unless you launched a different shell after logging in.
        
        $ echo $SHELL
        /bin/bash
* `ps`-show the processes running for the current user. The shell will be one of them.

        $ ps
          PID TTY       TIME CMD
        2148 pts/1      00:00:00 bash
        8756 pts/1      00:00:00 ps
####### Locate the AWS Completer
The location can vary depending on the installation method used.
* **Package Manager**-programs such as pip, yum, brew and apt-get typically install the AWS completer (or a symlink to it) to a standard path location. In this case, `which` will locate the completer for you.

        $ which aws_completer
        /usr/local/bin/aws_completer
* **Bundled Installer**-if you used the bundled installer per the instructions in the previous section, the AWS completer will be located in the `bin` subfolder of the installation directory.

        $ ls /usr/local/aws/bin
        activate
        activate.csh
        activate.fish
        activate_this.py
        aws
        aws.cmd
        aws_completer
        ...
If all else fails, you can use `find` to search your entire file system for the AWS completer.
`$ find / -name aws_completer`
`/usr/local/aws/bin/aws_completer`
####### Enable Command Completion
Run a command to enable command completion. The command that you use to enable completion depends on the shell that you are using. You can add the command to your shell's RC file to run it each time you open a new shell.
* **bash**-use the built-in command complete
    `$ complete -C '/usr/local/bin/aws_complete' aws`
    Add the command to `~/.bahsrc` to run it each time you open a new shell. Your `~/.bash_profile` should source `~/.bashrc` to ensure that the command is run in login shells as well.
####### Test Command Completion
After enabling command completion, type in a partial command and press TAB to see the available commands.

        $ aws sTAB
        s3  ses sqs sts swf
        s3api   sns storagegateway support

##### Deploying a Development Environment in Amazon EC2 Using the AWS Command Line Interface
This tutorial details how to set up a development environment in Amazon EC2 using the AWS CLI. It includes a short version of the installation and configuration instructions, and it can be run start to finish on Windows, Linux, macOS, or Unix.
###### Install the AWS CLI
You can install the AWS CLI with an installer (Windows) or by using pi, a package manager for Python.
* Windows
    Download the MSI installer.
    * [Download the AWS CLI MSI installer for Windows (64-bit)](https://s3.amazonaws.com/aws-cli/AWSCLI64.msi)
    * Download the AWS CLI MSI installer for Windows (32-bit)
* Linux, macOS, or Unix
    These steps require that you have a working installation of Python 2 version 2.6.5+ or Python 3 version 3.3+. If you encounter any issues using the following steps, see the full installation instructions in the AWS Command Line Interface User Guide.
    1. Download and run the installation script from the pip website:
        
        $ curl "https://bootstrap.pypa.io/get-pip.py" -o "get-pip.py"
        $ python get-pip.py --user
    2. Install the AWS CLI Using pip:

        $ pip install awscli --user
###### Configure the AWS CLI
Run `aws configure` at the command line to set up your credentials and settings.

        $ aws configure
        AWS Access Key ID [None]: AKIAIOSFODNN7EXAMPLE
        AWS Secret Access Key [None]: wJalrXUtnFEMI/K7MDENG/bPxRfiCYEXAMPLEKEY
        Default region name [None]: us-east-2
        Default output format [None]: json
The AWS CLI will prompt you for the following information:
* **AWS Access Key ID and AWS Secret Access Key**-These are your account credentials. If you don't have keys, see How Do I Get Security Credentials? in the Amazon Web Services General Reference.
* **Default region name**-This is the name of region you want to make calls against by default.
* **Default output format**-This format can be either json, text, or table. If you don't specify an output format, json will be used.
Run a command to verify that your credentials are configured correctly and that you can connect to AWS.

        $ aws ec2 describe-regions --output table
        ----------------------------------------------------------
        |                     DescribeRegions                    |
        +--------------------------------------------------------+
        ||                        Regions                       ||
        |+-----------------------------------+------------------+|
        ||             Endpoint              |   RegionName     ||
        |+-----------------------------------+------------------+|
        ||  ec2.ap-south-1.amazonaws.com     |  ap-south-1      ||
        ||  ec2.eu-west-3.amazonaws.com      |  eu-west-3       ||
        ||  ec2.eu-west-2.amazonaws.com      |  eu-west-2       ||
        ||  ec2.eu-west-1.amazonaws.com      |  eu-west-1       ||
        ||  ec2.ap-northeast-3.amazonaws.com |  ap-northeast-3  ||
        ||  ec2.ap-northeast-2.amazonaws.com |  ap-northeast-2  ||
        ||  ec2.ap-northeast-1.amazonaws.com |  ap-northeast-1  ||
        ||  ec2.sa-east-1.amazonaws.com      |  sa-east-1       ||
        ||  ec2.ca-central-1.amazonaws.com   |  ca-central-1    ||
        ||  ec2.ap-southeast-1.amazonaws.com |  ap-southeast-1  ||
        ||  ec2.ap-southeast-2.amazonaws.com |  ap-southeast-2  ||
        ||  ec2.eu-central-1.amazonaws.com   |  eu-central-1    ||
        ||  ec2.us-east-1.amazonaws.com      |  us-east-1       ||
        ||  ec2.us-east-2.amazonaws.com      |  us-east-2       ||
        ||  ec2.us-west-1.amazonaws.com      |  us-west-1       ||
        ||  ec2.us-west-2.amazonaws.com      |  us-west-2       ||
        |+-----------------------------------+------------------+|
###### Create a Security Group and Key Pair for the EC2 Instance
Your next step is to set up prerequisities for launching an EC2 instance that can be accessed using SSH. For more information about Amazon EC2 features, go to the [Amazon EC2 User Guide for Linux Instances](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/concepts.html)
**To create a security group, key pair, and role**
1. First, create a new security group and add a rule that allows incoming traffic over  port 22 for SSH. If you are using the default VPC for the region, you can omit the `--vpc-id` parameter; otherwise, specify the ID of the VPC in which you'll launch your instance. For better security, replace the 0.0.0.0/0 CIDR range with the range of the network from which you'll connect to your instance.

        $ aws ec2 create-security-group --group-name devenv-sg --vpc-id vpc-xxxxxxxx --description "security group for development environment"
        {
          "GroupId":"sg-b018ced5"
        }
        $ aws ec2 authorize-security-group-ingress --group-name devenv-sg --protocol tcp --port 22 --cidr 0.0.0.0/0
Note the security group ID for later use when you launch the instance.
2. Next, create the key pair, which allows you to connect to the instance. This command saves the contents of the key to a file named *devenv-key.pem*.
`$ aws ec2 create-key-pair --key-name devenv-key --query 'KeyMaterial' --output text > devenv-key.pem`
**Windows**: In a Windows Command prompt, use double quotes instead of single quotes.
3. On Linux, you will also need to change the file mode so that only you have access to the key file.
`$ chmod 400 devenv-key.pem`
###### Launch and connect to the Instance
Finally, you are ready to launch instance and connect to it.
**To launch and connect to the instance**
1. Run the following command, using the ID of the security group that you created in the previous step. The `--image-id` parameter specifies the Amazon Machine Image (AMI) that Amazon EC2 uses to bootstrap the instance. You can find an image ID for your region and operating system using the Amazon EC2 console. If you are using the default subnet for a default VPC, you can omit the `--subnet-id` parameter; otherwise, specify the ID of the subnet in which you'll launch your instance.
`$ aws ec2 run-instance --image-id ami-xxxxxxxx --subnet-id subnet-xxxxxxxx --security-group-ids sg-b018ced5 --count 1 --instance-type t2.micro --key-name devenv-key --query 'Instances[0].InstanceId'`
`"i-0787e4282810ef9cf"`
2. The instance will take a few moments to launch. After the instance is up and running, you'll need the public IP address of the instance to connect to it. Use the following command to get the public IP address:
`$ aws ec2 describe-instances --instance-ids i-0787e4282810ef9cf --query 'Reservation[0].Instances[0].PublicIpAddress'`
`"54.183.22.255"`
3. To connect to the instance, use the public IP address and private key with your preferred terminal program. On Linux, macOS, or Unix, you can do this from the command line using the following command:
`$ ssh -i devenv-key.pem <user>@<54.183.22.255>`
If you get an error like *Permission denied (publickey)* when attempting to connect to your instance, check that the following are correct:
* **Key**-The key specified must be at the path indicated and must be the private key, not the public one. Permissions on the key must be restricted to the owner.
* **User**-The user name must match the default user name associated wit the AMI you used to launch the instance. For an Ubuntu AMI, this is *ubuntu*.
* **Instance**-The public IP address or DNS name of the instance. Verify that the address is public and that port 22 is open to your local machine on the instance's security group.
You can also use the `-v` option to view additional information related to the error.
**SSH on Windows**
On Windows, you can use the PuTTY terminal application available [here](https://www.chiark.greenend.org.uk/~sgtatham/putty/). Get putty.exe and puttygen.exe from the download page.
Use puttygen.exe to convert your private key to a .ppk file required by PuTTY. Launhc putty.exe, enter the public IP address of the instance in the **Host Name** field, and set the connection type to SSH.
In the **Category** panel, navigate to **Connection**>**SSH**>**Auth**, and click **Browse** to select your .ppk file, and then click **Open** to connect.
4. The terminal will prompt you to accept the server's public key. Type *yes* and click **Enter** to complete the connection.
You've now configured a security group, created a key pair, launched an EC2 instance, and connected to it without ever leaving the command line.
##### Using the AWS Command Line Interface
This section introduces the common features and calling patterns used throughout the AWS Command Line Interface.
**Note**: The AWS CLI makes API calls to services over HTTPS. Outbound connections on TCP port 443 must be enabled in order to perform calls.
###### Getting Help with the AWS Command Line Interface
To get help when using the AWS CLI, you can simply add `help` to the end of a command. For example, the following command lists help for the general AWS CLI options and the available top-level commands.
`$ aws help`
The following command lists the available subcommands for Amazon EC2.
`$ aws ec2 help`
The next example lists the detailed help for the EC2 DescribeInstances operation, including descriptions of it input parameters, filters, and output. Check the examples section of the help if you are not sure how to phrase a command.
`$ aws ec2 describe-instances help`
The help for each command is divided into six sections:
* **Name**-the name of the command.
    
        NAME
            describe-instances -
* **Description**-a description of the API operation that the command invokes, pulled from the API documentation for the command's service.

        DESCRIPTION
            Describe one or more of your instances.

            If you specify one or more instance IDs, Amazon EC2 returns information for those instances. If you do not specify instance IDs, Amazon EC2 returns information for all relevant instances. If you specify an instance ID that is not valid, an error is returned. If you spescify an instance that you do not own, it is not included in the returened results.
        ...
* **Synosis**-list of the command and its options. If an option is shown in square brackets, it is either optional, has a default value, or has an alternative option that can be used instead.

        SYNOPSIS
            describe-instances
           [--dry-run | --no-dry-run]
           [--instance-ids <value>]
           [--filters <value>]
           [--cli-input-json <value>]
           [--starting-token <value>]
           [--page-size <value>]
           [--max-items <value>]
           [--generate-cli-skeleton]
     `describe-instances` has a default behavior that describes all instances in the current account and region. You can optionally specify a list of `instance-ids` to describe one or more instances. `dry-run` is an optional boolean flag that doesn't take a value. To use a boolean flag, specify either shown value, in this case `--dry-run` or `--no-dry-run`. Likewise, `--generate-cli-skeleton` does not take a value. If there are conditions on an option's use, they should be described in the OPTIONS section, or shown in the examples.
* **Options**- description of each of the options shown in the synopsis.

        OPTIONS
            --dry-run | --no-dry-run (boolean)
              Checks whether you have the requred permissions for the action, without actually making the request, and provides an error response.
              If you have the required permissions, the error response is DryRun-Operation. Otherwise, it is UnauthorizedOperation.
            --instance-ids (list)
              One or more instance IDs.

              Default: Describes all your instances.
* **Examples**-examples showing the usage of the command and its options. If no example is available for a command or use case that you need, please request one using feedback link on this page, or in the AWS CLI command reference on the help page for the command.

        EXAMPLES
        To describe an Amazon EC2 instance
        Command:
        aws ec2 describe-instances --instance-ids i-5203422c

        To describe all instances with the instance type m1.small
        command:
        aws ec2 describe-instances --filters "Name=instance-type, Values=m1.small"

        To describe all instances with a Owner tag
        Command:
        aws ec2 describe-instances --filters "Name=tag-key,values=Owner"
        ...
* **Output**-descriptions of each of the fields and datatypes returned in the response from AWS.
    For describe-instances, the output is a list of reservation objects, each of which contains several fields and objects that contain information about the instance(s) associated with it. This information comes from the API documentation for the reservation datatype used by Amazon EC2.

        OUTPUT
            Reservations -> (list)
             One or more reservations.

             (structure)
                Describes a reservation.

                ReservationId -> (string)
                  The ID of the reservation.

                OwnerId -> (string)
                  The ID of the AWS account that owns the reservation.

                RequestId -> (string)
                  The ID of the requester that launched the instances on your behalf ( for example, AWS Management Console or Auto Scaling).

                Groups -> (list)
                  One or more security groups.

                  (structure)
                    Describe a security group.

                    GroupName -> (string)
                      The name of the security group.

                    GroupId -> (string)
                      The ID of the security group.

                Instances -> (list)
                   One or more instances.

                   (structure)
                     Describes an instance.

                     InstanceId -> (string)
                       The ID of the instance.

                     ImageId -> (string)
                       The ID of the AMI used to launch the instance.

                    State -> (structure)
                      The current state of the instance.

                      Code -> (integer)
                        The low byte represents the state. The high byte is an opaque internal value and should be ignored.
    When the output is rendered into JSON by the AWS CLI, it becomes an array of reservation objects, like this:

        {
          "Reservations":[
            {
              "OwnerId":"012345678901",
              "ReservationId":"r-4c58f8a0",
              "Groups":[]
              "RequesterId":"012345678901",
              "Instances":[
                {
                  "Monitoring":{
                    "State":"disabled"
                  },
                  "PublicDnsName":"ec2-52-74-16-12.us-west-2.compute.amazonaws.com",
                  "State":{
                    "Code":16,
                    "Name":"running"
                  },
            ...
    Each reservation object contains fields describing the reservation and an array of instance objects, each with its own fields (e.g. PublicDnsName) and objects (e.g. State) that describe it.
**Windows Users**
Pipe the output of the help command to more to view the help file one page at a time. Press the space bar or PageDown to view more of the document, and q to quit.
`> aws ec2 describe-instances help | more`
###### Command Structure
The AWS CLI uses a multipart structure on the command line. It starts with the base call to `aws`. The next part specifies a top-level command, which often represents an AWS service supported in the AWS CLI. Each AWS service has additional subcommands that specify the operation to perform. The general CLI options, or the specific parameters for an operation, can be specified on the command line in any order. If an exclusive parameter is specified multiple times, then only the *last value* applies.
`$ aws <command> <subcommand> [options and parameters]`
Parameters can take various types of input values, such as numbers, strings, lists, maps, and JSON structures.
###### Specifying Parameter Values
Many parameters are simple string or numeric values, such as the key pair name my-key-pair in the following example:
`$ aws ec2 create-key-pair --key-name my-key-pair`
Strings without any space characters may be quoted or unquoted. However, strings that include one or more space characters must be quoted. Use a single quote (') in Linux, macOS, or Unix and Windows PowerShell, or use a double quote (") in the Windows command prompt, as shown in the following examples.
**Windows PowerShell, Linux, macOS, or Unix**
`$ aws ec2 create-key-pair --key-name 'my key pair'`
**Windows Command Processor**
`> aws ec2 create-key-pair --key-name "my key pair"`
You can also use an equals sign instead of a space. This is typically only necessary if the value of the parameter starts with a hyphen:
`aws ec2 delete-key-pair --key-name=-mykey`
####### Common Parameter Types
The section describes some of the common parameter types and the format that the services expect them to conform to. If you are having trouble with the formatting of a parameter for a specific command, check the manual by typing `help` after the command name, for example:
`$ aws ec2 describe-spot-price-history help`
The help for each subcommand describes its function, options, output, and examples. The options section includes the name and description of each option with the option's parameter type in parentheses.
* **String**-String parameters can contain alphanumeric characters, symbols, and whitespace from the ASCII character set. Strings that contain whitespace must be surrounded by quotes. Use of symbols and whitespace other than the standard space character is not recommended and may cause issues when using the AWS CLI.
    Some string parameters can accept binary data from a file. See Binary Files for an example.
* **Timestamp**-Timestamps are formatted per the ISO 8601 standard. These are sometimes referred to as "Date Time" or "Date" type parameters.
    `$ aws ec2 describe-spot-price-history --start-time 2014-10-13T19:00:00Z`
    Acceptable formats include:
    * YYYY-MM-DDThh:mm:ss.sssTZD (UTC), e.g., 2014-10-01T20:30:00.000Z
    * YYYY-MM-DDThh:mm:ss.sssTZD (with offset), e.g., 2014-10-01T12:30:00.000-08:00
    * YYYY-MM-DD, e.g., 2014-10-01
    * Unix time in seconds, e.g. 1412195400
* **List**-One or more strings separated by spaces
    `$ aws ec2 describe-spot-price-history --isntance-types m1.xlarge m1.medium`
* **Boolean**-Binary flag that turns an option on or off. For example, `ec2 describe-spot-price-history` has a boolean `dry-run` parameter that, when specified, validates the command against the service without actually running a query.
    `$ aws ec2 describe-spot-price-history --dry-run`
    The output indicates where the command was well formed or not. This command also includes a `no-dry-run` version of the parameter that can be used to explicitly indicate that the command should be run normally, although including it is not necessary as this is the default behavior.
* **Integer**-An unsigned whole number.
    `$ aws ec2 describe-spot-price-history --max-items 5`
* **Blob**-Binary object. Blob parameters take a path to a local file that contains binary data. The path should not contain any protocol identifier such as `http://` or `file://`.
    The `--body` parameter for `aws s3api put-object` is a blob:
    `$ aws s3api put-object --bucket my-bucket --key testimage.png --body /tmp/image.png`
* **Map**-A sequence of key value pairs specified in JSON or shorthand syntax. The following example reads an item from a DynamoDB table named *my-table* with a map parameter, `--key`. The parameter specifies the primary key named *id* with a number value of *1* in a nested JSON structure.

        $ aws dynamodb get-item --table-name my-table --key '{"id":{"N":"1"}}'
         {
           "Item":{
              "name":{
                "S":"John"
              },
              "id":{
                "N":"1"
              }
            }
          }
The next section covers JSON arguments in more detail.
####### Using JSON for Parameters
JSON is useful for specifying complex command line parameters. For example, the following command will list all EC2 instances that have an instance type of m1.small or m1.medium that are also in the us-west-2c Availability Zone.
`$ aws ec2 describe-instances --filters "Name=instance-type,Values=t2.micro,m1.medium" "Name=availability-zone,Values=us-west-2c"`
The following example specifies the equivalent list of filters in a JSON array. Square brackets are used to create an array of JSON objects separated by commas. Each object is a comma separated list of key-value pairs ("Name" and "Values" are both keys in this instance).
Note that value to the right of the "Values" key is itself an array. This is required, even if the array contains only one value string.

        [
         {
          "Name":"instance-type",
          "Values":["t2.micro","m1.medium"]
          },
          {
           "Name":"availability-zone",
           "Values":["us-west-2c"]
          }
         ]
The outermost brackets, on the other hand, are only required if more than one filter is specified. A single filter version of the above command, formatted in JSON, looks like this:
`$ aws ec2 describe-instances --filters '{"Name":"instance-type","Values":["t2.micro","m1.medium"]}'`
Some operations require data to be formatted as JSON. For example, to pass parameters to the `--block-device-mappings` parameter in the `ec2 run-instances` command, you need to format the block device information as JSON.
This example shows the JSON to specify a single 20GiB Elastic Block Store device to be mapped at `/dev/sdb` on the launching instance.

        {
         "DeviceName":"/dev/sdb",
         "Ebs":{
          "VolumeSize":20,
          "DeleteOnTermination":false,
          "VolumeType":"standard"
          }
         }
To attack multiple devices, list the objects in an array like in the next example.

        [
         {
          "DeviceName":"/dev/sdb",
          "Ebs":{
           "VolumeSize":20,
           "DeleteOnTermination":false,
           "VolumeType":"standard"
           }
          },
          {
           "DeviceName":"/dev/sdc",
           "Ebs":{
            "VolumeSize":10,
            "DeleteOnTermination":true,
            "VolumeType":"standard"
            }
           }
          ]
You can either enter the JSON directly on the command line (see Quoting Strings), or save it to a file that is referenced from the command line (see Loading Parameters from a File).
When passing in large blocks of data, you might find it easier to save the JSON to a file and reference it from the command line. JSON data in a file is easier to read, edit, and share with others. This technique is described in the next section.
####### Quoting Strings
The way you enter JSON-formatted parameters on the command line differs depending upon your operating system. Linux, macOS, or Unix and Windows PowerShell use the single quote(') to enclose the JSON data structure, as in the following example:
`$ aws ec2 run-instances --image-id ami-05355a6c --block-device-mappings '[{"DeviceName":"/dev/sdb","Ebs":{"VolumeSize":20,"DeleteOnTermination":false,"VolumeType":"standard"}}]'`
The Windows command prompt, on the other hand, uses the double quote (") to enclose the JSON data structure. In addition, a backslash (\) escape character is required for each double quote (") within the JSON data structure it self, as in the following example:
`> aws ec2 run-instances --image-id ami-05355a6c --block-device-mappings "[{\"DeviceName\":\"/dev/sdb\",\"Ebs\":{\"VolumeSize\":20,\"DeleteOnTermination\":false,\"VolumeType\":\"standard\"}}]"`
Windows PowerShell requires a single quote (') to enclose the JSON data structure, as well as a backslash (\) to escape double quote (") within the JSON structure, as in the following example:
`> aws ec2 run-instances --image-id ami-05355a6c --block-device-mappings '[{\"DeviceName\":\"/dev/sdb\",\"Ebs\":{\"VolumeSize\":20,\"DeleteOnTermination\":false,\"VolumeType\":\"standard\"}}]'`
####### Loading Parameters from a File
To avoid the need to escape JSON strings at the command line, load the JSON from a file. Load parameters from a file by providing the path to the file using the `file://` prefix, as in the following examples.
* **Linux, macOS, or Unix**

        //Read from a file in the current directory
        $ aws ec2 describe-instances --filters file://filter.json

        //Read from a file in /tmp
        $ aws ec2 describe-instances --filters file:///tmp/filter.json
* **Windows**

        //Read from a file in C:\temp
        > aws ec2 describe-instances --filters file://C:\temp\filter.json
The `file://` prefix option supports Unix-style expansions including `~/`, `./`, and `../`. On Windows, the `~/` expression expands to your user directory, stored in the `%USERPROFILE%` environment variable. For example, on Windows 7 you would typically have a user directory under `C:\Users\User Name\``.
JSON documents that are provided as the value of a parameter key must still be escaped:
`$ aws sqs create-queue --queue-name my-queue --attributes file://attributes.json`

**attributes.json**

        {
         "RedrivePolicy":"{\"deadLetterTargetArn\":\"arn:aws:sqs:us-west-2:0123456789012:deadletter\",\"maxReceiveCount\":\"5\"}"
        }
* **Binary Files**
    For commands that take binary data as a parameter, specify that the data is binary content by using the `fileb://` prefix. Commands that accept binary data include:
    * `aws ec2 run-instances`- `--user-data` parameter
    * `aws s3api put-object`- `--sse-customer-key` parameter
    * `aws kms decrypt`- `--ciphertext-blob` parameter
    The following example generates a binary 256 bit AES key using a Linux command line tool and then provides it to Amazon S3 to encrypt an uploaded file server-side:

        $ dd if=/dev/urandom bs=1 count=32 > sse.key
        32+0 records in
        32+0 records out
        32 bytes (32 B) coppied, 0.000164441 s, 195 kB/s
        $ aws s3api put-object --bucket my-bucket --key test.txt --body test.txt --sse-customer-key fileb://sse.key --sse-customer-algorithm AES256
        {
         "SSECustomerKeyMD5": "iVg8oWa8sy714+FjtesrJg==",
         "SSECustomerAlgorithm": "AES256",
         "ETag": "\"a6118e84b76cf98bf04bbe14b6045c6c\""
        }

* **Remote Files**
    The AWS CLI also supports loading parameters from a file hosted on the Internet with an `http://` URL. The following example references a file in an Amazon S3 bucket. This allows you to access parameter files from any computer, but requires the file to be stored in a publically accessible location.
    `$ aws ec2 run-instances --image-id ami-a13d6891 --block-device-mamppings http://my-bucket.s3.amazonaws.com/filename.json`
    In the preceding examples, the `filename.json` file contains the following JSON data.

        [
         {
          "DeviceName":"/dev/sdb",
          "Ebs":{
           "VolumeSize":20,
           "DeleteOnTermination":false,
           "VolumeType":"standard"
           }
          }
         ]

###### Generate CLI Skeleton and CLI Input JSON Parameters
Most AWS CLI commands support `--generate-cli-skeleton` and `--cli-input-json` parameters that you can use to store parameters in JSON and read them from a file instead of typing them at the command line.
Generate CLI Skeleton outputs JSON that outlines all of the parameters that can be specified or the operation.
**To use `--generate-cli-skeleton` with aws ec2 run-instances**
1. Execute the `run-instances` command with the `--generate-cli-skeleton` option to view the JSON skeleton.

        $ aws ec2 run-instances --generate-cli-skeleton
        {
            "DryRun": true,
            "ImageId": "",
            "MinCount": 0,
            "MaxCount": 0,
            "KeyName": "",
            "SecurityGroups": [
                ""
            ],
            "SecurityGroupIds": [
                ""
            ],
            "UserData": "",
            "InstanceType": "",
            "Placement": {
                "AvailabilityZone": "",
                "GroupName": "",
                "Tenancy": ""
            },
            "KernelId": "",
            "RamdiskId": "",
            "BlockDeviceMappings": [
                {
                    "VirtualName": "",
                    "DeviceName": "",
                    "Ebs": {
                        "SnapshotId": "",
                        "VolumeSize": 0,
                        "DeleteOnTermination": true,
                        "VolumeType": "",
                        "Iops": 0,
                        "Encrypted": true
                    },
                    "NoDevice": ""
                }
            ],
            "Monitoring": {
                "Enabled": true
            },
            "SubnetId": "",
            "DisableApiTermination": true,
            "InstanceInitiatedShutdownBehavior": "",
            "PrivateIpAddress": "",
            "ClientToken": "",
            "AdditionalInfo": "",
            "NetworkInterfaces": [
                {
                    "NetworkInterfaceId": "",
                    "DeviceIndex": 0,
                    "SubnetId": "",
                    "Description": "",
                    "PrivateIpAddress": "",
                    "Groups": [
                        ""
                    ],
                    "DeleteOnTermination": true,
                    "PrivateIpAddresses": [
                        {
                            "PrivateIpAddress": "",
                            "Primary": true
                        }
                    ],
                    "SecondaryPrivateIpAddressCount": 0,
                    "AssociatePublicIpAddress": true
                }
            ],
            "IamInstanceProfile": {
                "Arn": "",
                "Name": ""
            },
            "EbsOptimized": true
        }

2. Direct the output to a file to save the skeleton locally:
`$ aws ec2 run-instances --generate-cli-skeleton > ec2runinst.json`
3. Open the skeleton in text editor and remove any parameters that you will not use:

        {
          "DryRun":true,
          "ImageId":"",
          "KeyName":"",
          "SecurityGroups":[
            ""
          ],
          "InstanceType":"",
          "Monitoring":{
            "Enabled":true
          }
         }
    Leave the DryRun parameter set to true to use EC2's dry run feature, which lets you test your configuration without creating resources.
4. Fill in the values for the instance type, key name, security group and AMI in you default region. In this example, `ami-dfc39aef` is a 64-bit Amazon Linux image in the `us-west-2` region.

        {
          "DryRun":true,
          "ImageId":"ami-dfc39aef",
          "KeyName":"mykey",
          "SecurityGroups":[
            "my-sg"
          ],
          "InstanceType":"t2.micro",
          "Monitoring":{
            "Enabled":true
          }
         }

5. Pass the JSON configuration to the `--cli-input-json` parameter using the `file://` prefix:

        $ aws ec2 run-instances --cli-input-json file://ec2runinst.json
        A client error (DryRunOperation) occurred when calling the RunInstances operation: Request would have succeeded, but DryRun flag is set.
    The dry run error indicates that the JSON is formed correctly and the parameter values are valid. If any other issues are reported in the output, fix them and repeat the above step until the dry run error is shown.
6. Set the DryRun parameter to false to disable the dry run feature.

        {
          "DryRun":false,
          "ImageId":"ami-dfc39aef",
          "KeyName":"mykey",
          "SecurityGroups":[
            "my-sg"
          ],
          "InstanceType":"t2.micro",
          "Monitoring":{
            "Enabled":true
          }
         }

7. Run the `run-instances` command again to launch an instance:

        $ aws ec2 run-instances --cli-input-json file://ec2runinst.json
        {
          "OwnerId":"123456789012",
          "ReservationId":"r-d94a2b1",
          "Groups":[],
          "Instances":[
        ...
###### Controlling Command Output from the AWS Command Line Interface
This section describes the different ways that you can control the output from the AWS CLI.
####### How to Select the Output Format
The AWS CLI supports three different output formats:
* JSON (json)
* Tab-delimited text (text)
* ASCII-formatted table (table)
As explained in the configuration topic, the output format can be specified in three different ways:
* Using the `output` option in the configuration file. The following example sets the output to text:

        [default]
        output=text
* Using the AWS_DEFAULT_OUTPUT environment variable. For example:
    `$ export AWS_DEFAULT_OUTPUT="table"`
* Using the `--output` option on the command line. For example:
    `$ aws swf list-domains --registration-status REGISTERED --output text`
**Note**:If the output format is specified in multiple ways, the usual AWS CLI precedence rules apply. For example, using the AWS_DEFAULT_OUTPUT environment variable overrides any value set in the config file with `output`, and a value passed to an AWS CLI command with `--output` overrides any value set in the environment or in the config file.
JSON is best for handling the output programmatically via various languages. The table format is easy for humans to read, and text format works well with traditional Unix text processing tools, such as `sed`, `grep`, and `awk`, as well as Windows PowerShell scripts.
####### How to Filter the Output with the `query` Option
The AWS CLI provides built-in output filtering capabilities with the `--query` option. To demonstrates how it works, we'll first start with the default JSON output below, which describes two EBS (Elastic Block Storage) volumes attached to separate EC2 instances.

        {
            "Volumes": [
                {
                    "AvailabilityZone": "us-west-2a",
                    "Attachments": [
                        {
                            "AttachTime": "2013-09-17T00:55:03.000Z",
                            "InstanceId": "i-a071c394",
                            "VolumeId": "vol-e11a5288",
                            "State": "attached",
                            "DeleteOnTermination": true,
                            "Device": "/dev/sda1"
                        }
                    ],
                    "VolumeType": "standard",
                    "VolumeId": "vol-e11a5288",
                    "State": "in-use",
                    "SnapshotId": "snap-f23ec1c8",
                    "CreateTime": "2013-09-17T00:55:03.000Z",
                    "Size": 30
                },
                {
                    "AvailabilityZone": "us-west-2a",
                    "Attachments": [
                        {
                            "AttachTime": "2013-09-18T20:26:16.000Z",
                            "InstanceId": "i-4b41a37c",
                            "VolumeId": "vol-2e410a47",
                            "State": "attached",
                            "DeleteOnTermination": true,
                            "Device": "/dev/sda1"
                        }
                    ],
                    "VolumeType": "standard",
                    "VolumeId": "vol-2e410a47",
                    "State": "in-use",
                    "SnapshotId": "snap-708e8348",
                    "CreateTime": "2013-09-18T20:26:15.000Z",
                    "Size": 8
                }
            ]
        }
First, we can display only the first volume from the Volumes list with the following command.

        $ aws ec2 describe-volumes --query 'Volumes[0]'
        {
            "AvailabilityZone": "us-west-2a",
            "Attachments": [
                {
                    "AttachTime": "2013-09-17T00:55:03.000Z",
                    "InstanceId": "i-a071c394",
                    "VolumeId": "vol-e11a5288",
                    "State": "attached",
                    "DeleteOnTermination": true,
                    "Device": "/dev/sda1"
                }
            ],
            "VolumeType": "standard",
            "VolumeId": "vol-e11a5288",
            "State": "in-use",
            "SnapshotId": "snap-f23ec1c8",
            "CreateTime": "2013-09-17T00:55:03.000Z",
            "Size": 30
        }
Now, we use the wildcard `[*]` to iterate the entire list and also filter out three elements: VolumeId, AvailabilityZone, and Size. Note that the dictionary notation requires that you provide an alias for each key, like this: `Alias1:Key1,Alias2:Key2}`. A dictionary is inherently *unordered*, so the ordering of the key-aliases within a structure may not be consistent in some cases.

        $ aws ec2 describe-volumes --query 'Volumes[*].{ID:VolumeId,AZ:AvailabilityZone,Size:Size}'
        [
          {
            "AZ":"us-west-2a",
            "ID":"vol-e11a5288",
            "Size":30
          },
          {
            "AZ":"us-west-2a",
            "ID":"vol-2e410a47",
            "Size":8
          }
         ]
In the dictionary notation, you can also use chained keys such as key1.key2[0].key3 to filter elements deeply nested within the structure. The example below demonstrates this with the Attachments[0].InstanceId key, aliased to simply InstanceId.

        $ aws ec2 describe-volumes --query 'Volumes[*].{ID:VolumeId,InstanceId:Attachements[0].InstanceId,AZ:AvailableZone,Size:Size}'
        [
          {
            "InstanceId":"i-a071c394",
            "AZ":"us-west-2a",
            "ID":"vol-e11a5288",
            "Size":30
          },
          {
            "InstanceId":"i-4b41a37c",
            "AZ":"us-west-2a",
            "ID":"vol-2e410a47",
            "Size":8
          }
        ]
You can also filter multiple elements with the list notation: [key1,key2]. This will format all filtered attributes into a single *ordered* list per object, regardless of type.

        $ aws ec2 describe-volumes --query 'Volumes[*].[VolumeId, Attachments[0],InstanceId,AvailableZone,Size]'
        [
          [
            "vol-e11a5288",
            "i-a071c394",
            "us-west-2a",
            30
          ],
          [
            "vol-2e410a47",
            "i-4b41a37c",
            "us-west-2a",
            8
          ]
         ]
To filter results by the value of a specific field, use the JMESPath `?` operator. The following example query outputs only volumes ion the us-west-2a availability zone:

        $ aws ec2 describe-volums --query 'Volumes[?AvailabilityZone==`us-west-2a`]'
**Note**: When specifying a literal value such as "us-west-2" above in a JMESPath query expression, you must surround the value in backticks (\`) in order for it to be read properly.
Combined with the three output formats that will be explained in more detail in the following sections, the `--query` option is a powerful tool you can use to customize the content and style of outputs.
####### JSON Output Format
JSON is the default output format of the AWS CLI. Most languages can easily decode JSON strings using built-in functions or with publicly available libraries. As shown in the previous topic along with the output examples, the `--query` option provides powerful ways to filter and format the AWS CLI's JSON formatted output. If you need more advanced features that may not be possible with `--query`, you can check out jq, a command line JSON processor.
####### Test Output Format
The *text* format organizes the AWS CLI's output into tab-delimited lines. It works well with traditional Unix text tools such as grep, sed, and awk, as well as Windows PowerShell.
The text output format follows the basic structure shown below. The columns are sorted alphabetically by the corresponding key names of the underlying JSON object.

        IDENTIFIER sorted-column1 sorted-column2
        IDENTIFIER2 sorted-column1 sorted-column2
The following is an example of a text output.

        $ aws describe-volumes --output text
        VOLUMES us-west-2a 2013-09-17T00:55:03.000Z 30  snap-f23ec1c8 in-use vol-e11a5288 standard
        ATTACHMENTS     2013-09-17T00:55:03.000Z        True    /dev/sda1       i-a071c394      attached        vol-e11a5288
        VOLUMES us-west-2a      2013-09-18T20:26:15.000Z        8       snap-708e8348   in-use  vol-2e410a47    standard
        ATTACHMENTS     2013-09-18T20:26:16.000Z        True    /dev/sda1       i-4b41a37c      attached        vol-2e410a47
We strongly recommend that the text output be used along with the `--query` option to ensure consistent behavior. This is because the text format alphabetically orders output columns, and similar resources may not always have the same collection of keys. For example, a JSON representation of a Linux EC2 instance may have elements that are not present in the JSON representation of a Windows instance, or vice versa. Also, resources may have key-value elements added or removed in future updates, altering the column ordering. This is where the `--query` arguments the functionality of the text output to enable complete control over the output format. In the example below, the command pre-selects which elements to display and defines the ordering of the columns with the list notation [key1,key2,...]. This gives users full confidence that the correct key values will always be displayed in the expected column. Finally, notice how the AWS CLI outputs 'None' as values for keys that don't exist.

        $ aws ec2 descirbe-volumes --query 'Volumes[*].[VolumeId,Attachments[0].InstanceId,AvailableZone,Size,FakeKey]' --output text
        vol-e11a5288 i-a071c394 us-west-2a 30 None
        vol-2e410a47 i-4b41a37c us-west-2a 8  None
Below is an example of how `grep` and `awk` can be used along with a text output from `aws ec2 describe-instances` command. The first command displays the AvailabilityZone, state, and instance ID of each instance in text output. The second command outputs only the instance IDs of all running instances in the `us-west-2a` Availability Zone.

        $ aws ec2 describe-instances --query 'Reservations[*].Instances[*].[Placement.AvailableZone,State.Name,InstanceId]' --output text
        us-west-2a running i-4b41a37c
        us-west-2a      stopped i-a071c394
        us-west-2b      stopped i-97a217a0
        us-west-2a      running i-3045b007
        us-west-2a      running i-6fc67758

        $ aws ec2 describe-instances --query 'Reservations[*].Instances[*].[Placement.AvailabilityZone,State.Name,InstanceId]' --output text | grep us-west-2a|grep running|awk '{print $3}'
        i-4b41a37c
        i-3045b007
        i-6fc67758
The next command shows a similar example for all stopped instances and takes it one step further to automate changing instance types for each stopped instance.

        $ aws ec2 describe-instances --query 'Reservations[*].Instances[*]].[State.Name,InstanceId]' --output text|
        > grep stopped|
        > awk '{print $2}'|
        > while read line;
        > do aws ec2 modify-instance-attribute --instance-id $line --instance-type '{"Value":"m1.medium"}';
        > done
####### Table Output Format
The table format produces human-readable representations of AWS CLI output. Here is an example:

        $ aws ec2 describe-volumes --output table
        ---------------------------------------------------------------------------------------------------------------------
        |                                                  DescribeVolumes                                                  |
        +-------------------------------------------------------------------------------------------------------------------+
        ||                                                     Volumes                                                     ||
        |+------------------+---------------------------+-------+----------------+---------+----------------+--------------+|
        || AvailabilityZone |        CreateTime         | Size  |  SnapshotId    |  State  |   VolumeId     | VolumeType   ||
        |+------------------+---------------------------+-------+----------------+---------+----------------+--------------+|
        ||  us-west-2a      |  2013-09-17T00:55:03.000Z |  30   |  snap-f23ec1c8 |  in-use |  vol-e11a5288  |  standard    ||
        |+------------------+---------------------------+-------+----------------+---------+----------------+--------------+|
        |||                                                  Attachments                                                  |||
        ||+---------------------------+------------------------+-------------+--------------+------------+----------------+||
        |||        AttachTime         |  DeleteOnTermination   |   Device    | InstanceId   |   State    |   VolumeId     |||
        ||+---------------------------+------------------------+-------------+--------------+------------+----------------+||
        |||  2013-09-17T00:55:03.000Z |  True                  |  /dev/sda1  |  i-a071c394  |  attached  |  vol-e11a5288  |||
        ||+---------------------------+------------------------+-------------+--------------+------------+----------------+||
        ||                                                     Volumes                                                     ||
        |+------------------+---------------------------+-------+----------------+---------+----------------+--------------+|
        || AvailabilityZone |        CreateTime         | Size  |  SnapshotId    |  State  |   VolumeId     | VolumeType   ||
        |+------------------+---------------------------+-------+----------------+---------+----------------+--------------+|
        ||  us-west-2a      |  2013-09-18T20:26:15.000Z |  8    |  snap-708e8348 |  in-use |  vol-2e410a47  |  standard    ||
        |+------------------+---------------------------+-------+----------------+---------+----------------+--------------+|
        |||                                                  Attachments                                                  |||
        ||+---------------------------+------------------------+-------------+--------------+------------+----------------+||
        |||        AttachTime         |  DeleteOnTermination   |   Device    | InstanceId   |   State    |   VolumeId     |||
        ||+---------------------------+------------------------+-------------+--------------+------------+----------------+||
        |||  2013-09-18T20:26:16.000Z |  True                  |  /dev/sda1  |  i-4b41a37c  |  attached  |  vol-2e410a47  |||
        ||+---------------------------+------------------------+-------------+--------------+------------+----------------+||
The `--query` option can be used with the table format to display a set of elements pre-selected from the raw output. Note the output differences in dictionary and list notations: column names are alphabetically ordered in the first example, and unnamed columns are ordered as defined by the user in the second example.

        $ aws ec2 describe-volumns --query 'Volumes[*].{ID:VolumeId,InstanceId:Attachements[0].InstanceId,AZ:AvailabilityZone,Size:Size}' --output table
        ------------------------------------------------------
        |                   DescribeVolumes                  | 
        +------------+----------------+--------------+-------+
        |     AZ     |      ID        | InstanceId   | Size  |
        +------------+----------------+--------------+-------+
        |  us-west-2a|  vol-e11a5288  |  i-a071c394  |  30   |
        |  us-west-2a|  vol-2e410a47  |  i-4b41a37c  |  8    |
        +------------+----------------+--------------+-------+

        $ aws ec2 describe-volumes --query 'Volumns[*].[VolumeId,Attachments[0].InstanceId,AvailabilityZone,Size]' --output table
        ----------------------------------------------------
        |                  DescribeVolumes                 |
        +--------------+--------------+--------------+-----+
        |  vol-e11a5288|  i-a071c394  |  us-west-2a  |  30 |
        |  vol-2e410a47|  i-4b41a37c  |  us-west-2a  |  8  |
        +--------------+--------------+--------------+-----+
###### Using Shorthand Syntax with the AWS Command Line Interface
While the AWS Command Line Interface can take nonscalar option parameters in JSON format, it can be tedious to type large JSON lists or structures on the command line. To address this issue, the AWS CLI supports a shorthand syntax that allows simpler representation of your option parameters than using the full JSON format.
####### Structure Parameters
The shorthand syntax in the AWS CLI makes it easier for users to input parameters that are flat (non-nested structures). The format is a comma separate list of key value pairs:
* Linux, macOS, or Unix
    `--option key1=value1, key2=value2,key3=value3`
* Windows PowerShell
    `--option "key1=value1,key2=value2,key3=value3"`
This is equivalent to the following example formatted in JSON:
`--option '{"Key1":"Value1","Key2":"Value2","Key3":"Value3"`
There must be no whitespace between each comma-separated key/value pair. Here is an example of the DynamoDB `update-table` command with the `--provisioned-throughput` option specified in shorthand.
`$ aws dynamodb udpate-table --provisioned-throughput ReadCapacityUnits=15,WriteCapacityUnits=10 --table-name MyDDBTable`
####### List Parameters
Input parameters in a list form can be specified in two ways: JSON and shorthand. The AWS CLI's shorthand syntax is designed to make it easier to pass lists with number, string, or non-nested structures. The basic format is shown here, where values in the list are separated by single space.
`--option value1 value2 value3`
This is equivalent to the following example formatted in JSON.
`--option '[value1,value2,value3]'`
As previously mentioned, you can specify a list of numbers, a list of strings, or a list of non-nested structures in shorthand. The following is an example of the `stop-instances` command for Amazon EC2, where the input parameters (list of strings) or the `--instance-ids` option is specified in shorthand.
`$ aws ec2 stop-instances --instance-ids i-1486157a i-1286157c i-ec3a7e87`
This is equivalent to the following example formatted in JSON.
`$ aws ec2 stop-instances --instance-ids '["i-1486157a","i-1286157c","i-ec3a7e87"]'`
Next is an example of the Amazon EC2 `create-tags` command, which takes a list of non-nested structures for the `--tags` option. The `--resoursces` option specifies the ID of the instance to be tagged.
`$ aws ec2 create-tags --resoursces i-1286157c --tags Key=My1stTag,Value=Value1 Key=My2ndTag,Value2 Key=My3rdTag,Value=Value3`
This is equivalent to the following example formatted in JSON. The JSON parameter is written in multiple lines of readability.

        $ aws ec2 create-tags --resources i-1286157c --tags '[
          {"Key":"My1stTag","Value":"Value1"},
          {"Key":"My2ndTag","Value":"Value2"},
          {"Key":"My3rdTag","Value":"Value3"}
        ]'
##### Using Amazon EC2 through the AWS Command Line Interface
You can access the features of Amazon EC2 using the AWS CLI. To list the AWS CLI commands for Amazon EC2, use the following command.
`$ aws ec2 help`
Before you run any commands, set your default credentials.
For examples for common tasks for Amazon EC2, see the following topics.
###### Using Key Pairs
You can use the AWS CLI to create, display, and delete your key pairs. You must specify a key pair when you launch and connect to an Amazon EC2 instance.
**Note**: Before you try the example commands, set your default credentials.
####### Creating a Key Pair
To create a key pair named "MyKeyPair", use the `create-key-pair` command, and use the `--query` option and the `--output text` option to pipe your private key directly into a file.
`$ aws ec2 create-key-pair --key-name MyKeyPair --query 'KeyMaterial' --output text > MyKeyPair.pem`
Note that for Windows PowerShell, the `>` file redirection defaults to UTF-8 encoding, which cannot be used with some SSH clients. So, you must explicitly specify ASCII encoding in the `out-file` command.
`aws ec2 create-key-pair --key-name MyKeyPair --query 'KeyMaterial' --output text | out-file -encoding ascii -filepath MyKeyPair.pem`
The resulting MyKeyPair.pem file looks like this:

        -----BEGIN RSA PRIVATE KEY-----
        EXAMPLEKEYKCAQEAy7WZhaDsrA1W3mRlQtvhwyORRX8gnxgDAfRt/gx42kWXsT4rXE/b5CpSgie/
        vBoU7jLxx92pNHoFnByP+Dc21eyyz6CvjTmWA0JwfWiW5/akH7iO5dSrvC7dQkW2duV5QuUdE0QW
        Z/aNxMniGQE6XAgfwlnXVBwrerrQo+ZWQeqiUwwMkuEbLeJFLhMCvYURpUMSC1oehm449ilx9X1F
        G50TCFeOzfl8dqqCP6GzbPaIjiU19xX/azOR9V+tpUOzEL+wmXnZt3/nHPQ5xvD2OJH67km6SuPW
        oPzev/D8V+x4+bHthfSjR9Y7DvQFjfBVwHXigBdtZcU2/wei8D/HYwIDAQABAoIBAGZ1kaEvnrqu
        /uler7vgIn5m7lN5LKw4hJLAIW6tUT/fzvtcHK0SkbQCQXuriHmQ2MQyJX/0kn2NfjLV/ufGxbL1
        mb5qwMGUnEpJaZD6QSSs3kICLwWUYUiGfc0uiSbmJoap/GTLU0W5Mfcv36PaBUNy5p53V6G7hXb2
        bahyWyJNfjLe4M86yd2YK3V2CmK+X/BOsShnJ36+hjrXPPWmV3N9zEmCdJjA+K15DYmhm/tJWSD9
        81oGk9TopEp7CkIfatEATyyZiVqoRq6k64iuM9JkA3OzdXzMQexXVJ1TLZVEH0E7bhlY9d8O1ozR
        oQs/FiZNAx2iijCWyv0lpjE73+kCgYEA9mZtyhkHkFDpwrSM1APaL8oNAbbjwEy7Z5Mqfql+lIp1
        YkriL0DbLXlvRAH+yHPRit2hHOjtUNZh4Axv+cpg09qbUI3+43eEy24B7G/Uh+GTfbjsXsOxQx/x
        p9otyVwc7hsQ5TA5PZb+mvkJ5OBEKzet9XcKwONBYELGhnEPe7cCgYEA06Vgov6YHleHui9kHuws
        ayav0elc5zkxjF9nfHFJRry21R1trw2Vdpn+9g481URrpzWVOEihvm+xTtmaZlSp//lkq75XDwnU
        WA8gkn6O3QE3fq2yN98BURsAKdJfJ5RL1HvGQvTe10HLYYXpJnEkHv+Unl2ajLivWUt5pbBrKbUC
        gYBjbO+OZk0sCcpZ29sbzjYjpIddErySIyRX5gV2uNQwAjLdp9PfN295yQ+BxMBXiIycWVQiw0bH
        oMo7yykABY7Ozd5wQewBQ4AdSlWSX4nGDtsiFxWiI5sKuAAeOCbTosy1s8w8fxoJ5Tz1sdoxNeGs
        Arq6Wv/G16zQuAE9zK9vvwKBgF+09VI/1wJBirsDGz9whVWfFPrTkJNvJZzYt69qezxlsjgFKshy
        WBhd4xHZtmCqpBPlAymEjr/TOlbxyARmXMnIOWIAnNXMGB4KGSyl1mzSVAoQ+fqR+cJ3d0dyPl1j
        jjb0Ed/NY8frlNDxAVHE8BSkdsx2f6ELEyBKJSRr9snRAoGAMrTwYneXzvTskF/S5Fyu0iOegLDa
        NWUH38v/nDCgEpIXD5Hn3qAEcju1IjmbwlvtW+nY2jVhv7UGd8MjwUTNGItdb6nsYqM2asrnF3qS
        VRkAKKKYeGjkpUfVTrW0YFjXkfcrR/V+QFL5OndHAKJXjW7a4ejJLncTzmZSpYzwApc=
        -----END RSA PRIVATE KEY-----
Your private key is not stored in AWS and can only be retrieved when it is created.
If you're sing an SSH client on a Linux computer to connect to your instance, use the following command to set the permissions of your private key file so that only you can read it.
`$ chmod 400 MyKeyPair.pem`
####### Displaying Your Key Pair
A fingerprint is generated from your key pair, and you can use to verify that the private key that you have on your local machine matches the public key that's stored in AWS. The fingerprint is an SHA1 hahs take from a DER encoded copy of the private key. This value is stored in AWS and can be viewed in the EC2 management console or by calling `aws ec2 describe-key-pairs`. For example, you can view the fingerprint for MyKeyPair using the following command:

        $ aws ec2 describe-key-pairs --key-name MyKeyPair
        {
          "KeyPairs":[
            {
              "KeyName":"MyKeyPair",
              "KeyFingerprint":"1f:51:ae:28:bf:89:e9:d8:1f:25:5d:37:2d:7d:b8:ca:9f:f5:f1:6f"
            }
          ]
        }
####### Deleting Your Key Pair
To delete MyKeyPair, use the `delete-key-pair` command as follows:
`$ aws ec2 delete-key-pair --key-name MyKeyPair`
###### Using Security Groups
You create a security group for use in either EC2-Classic or EC2-VPC. For more information about EC2-Classic and EC2-VPC, see Supported Platforms in the Amazon EC2 User Guide for Linux Instances.
You can use the AWS CLI to create, add rules to, and delete your security groups.
**Note**: Before you try the example commands, set your default credentials.
####### Creating a Security Group
To create a security group named my-sg, use the `create-security-group` command.
######## EC2-VPC
The following command creates a security group named my-sg for the specified VPC:

        aws ec2 create-security-group --group-name my-sg --description "My security group" --vpc-id vpc-1a2b3c4d
        {
          "GroupId":"sg-903004f8"
        }
To view the initial information for my-sg, use the `describe-security-groups` command as follows. Note that you can't reference a security group for EC2-VPC by name.

        aws ec2 describe-security-groups --group-ids sg-903004f8
        {
          "SecurityGroups":[
            {
               "IpPermissionsEgress":[
                 {
                   "IpProtocol":"-1",
                   "IpRanges":[
                     {
                       "CidrIp":"0.0.0.0/0"
                     }
                   ],
                   "UserIdGroupPairs":[]
                  }
                ],
                "Description":"My security group"
                "IpPermissions":[],
                "GroupName":"my-sg",
                "VpcId":"vpc-1a2b3c4d",
                "OwnerId":"123456789012",
                "GroupId":"sg-903004f8"
              }
            ]
        }
######## EC2-Classic
The following command creates a security group for EC2-Classic:

        aws ec2 create-sescurity-group --group-name my-sg --description "My security group"
        {
          "GroupId":"sg-903004f8"
        }
To view the initial information for my-sg, use the `describe-security-groups` command as follows:

        aws ec2 describe-security-groups --group-names my-sg
        {
          "SecurityGroups":[
            {
              "IpPermissionsEgress":[],
              "Description":"My security group",
              "IpPermissions":[].
              "GroupName":"my-sg",
              "OwnerId":"123456789012",
              "GroupId":"sg-903004f8"
            }
          ]
        }
####### Adding Rules to Your Security Group
If you're launching a Windows instance, you must add a rule to allow inbound traffic on TCP port (RDP). If you're launching a Linux instance, yo must add a rule to allow inbound traffic on TCP port 22 (SSH). Use the `authorize-security-group-ingress` command to add a rule to your security group. One of the required parameters of this command is the public IP address of your computer, in CIDR notation.
**Note**: You can get the public IP address of your local computer using a service. For example, we provide the following service:
https://checkip.amazonaws.com/. To locate another service that provides your IP address, use the search phrase "what is my IP address". If you are connecting through an ISP or from behind you firewall without s static IP address, you need to find out the range of IP addresses used by client computers.
######## EC2-VPC
The following command adds a rule for RDP to the security group with the ID sg-903004f8:
`aws ec2 authorize-security-group-ingress --group-id sg-903004f8 --protocol tc --port 3389 -cidr 203.0.113.0/24`
The following command adds a rule for SSH to the security group with the ID sg-903004f8:
`aws ec2 authorize-security-group-ingress --group-id sg-903004f8 --protocol tcp --port 22 cidr 203.0.113.0/24`
To view the changes to my-sg, use the `describe-security-groups` command as follows:

        aws ec2 describe-security-groups --group-ids sg-903004f8
        {
          "SecurityGroups":[
            {
              "IpPermissionsEgress":[
                {
                  "IpProtocol":"-1",
                  "IpRanges":[
                    {
                      "CidrIp":"0.0.0.0/0"
                    }
                  ],
                  "UserIdGroupPairs":[]
                }
              ],
              "Description":"My security group"
              "IpPermissions":[
                {
                  "ToPort":22,
                  "IpProtocol":"tcp",
                  "IpRanges":[
                    {
                      "CidrIp":"203.0.113.0/24"
                    }
                  ]
                  "UserIdGroupPairs":[],
                  "FromPort":22
                }
              ],
              "GroupName":"my-sg",
              "OwnerId":"123456789012",
              "GroupId":"sg-903004f8"
            }
          ]
        }
######## EC2-Classic
The following command adds a rule for RDP to the security group my-sg:
`aws ec2 autorize-security-group-ingress --group-name my-sg --protocol tcp --port 3389 --cidr 203.0.113.0/24`
The following command adds a rule for SSH to the security group for my-sg:
        
        aws ec2 authorize-security-group-ingress --group-names my-sg
        {
          "IpPermissionsEgress":[],
          "Description":"My security group"
          "IpPermissions":[
            {
              "ToPort":22,
              "IpProtocol":"tcp",
              "IpRanges":[
                {
                  "CidrIp":"203.0.113.0/24"
                }
              ]
              "UserIdGroupPairs":[],
              "FromPort":22
            }
           ],
           "GroupName":"my-sg",
           "OwnerId":"123456789012",
           "GroupId":"sg-903004f8"
          }
        ]
        }
####### Deleting Your Security Group
To delete a security group, use the `delete-security-group` command. Note that you can't delete a security group if it is attached to an environment.
######## EC2-VPC
The following command deletes the security group with the ID sg-903004f8:
`aws ec2 delete-security-group --group-id sg-903004f8`
######## EC2-Classic
`aws ec2 delete-sescurity-group --group-name my-sg`
###### Using Amazon EC2 Instances
You can use the AWS CLI to launch, list, and terminate instances. You'll need a key pair and a security group; for information about creating these  through the AWS CLI, see Using Key Pairs and Using Security Groups. You'll also need to select an Amazon Machine Image (AMI) and note its AMI ID. For more information, see Finding a Suitable AMI in the Amazon EC2 User Guide for Linux Instances.
If you launch an instance that is not within the AWS Free Tier, you are billed after yo launch the instance and charged for the time that the instance is running, even if it remains idle.
**Note**: Before you try the example command, set your default credentials.
####### Launching an Instance
To launch a single Amazon EC2 instance using the AMI you selected, use the `run-instances` command. Depending on the platforms that your account supports, you can launch the instance into EC2-Classic or EC2-VPC.
Initially, your instance is in the `pending` state, but will be in the `running` state in a few minutes.
######## EC2-VPC
The following command launches a t2.micro instance in the specified subnet:

        aws ec2 run-instances --image-id ami-xxxxxxxxx --count 1 --instance-type t2.micro --key-name MyKeyPair --security-group-ids sg-xxxxxxxx --subnet-id subnet-xxxxxxxx
        {
            "OwnerId": "123456789012",
            "ReservationId": "r-5875ca20",
            "Groups": [
                {
                    "GroupName": "my-sg",
                    "GroupId": "sg-903004f8"
                }
            ],
            "Instances": [
                {
                    "Monitoring": {
                        "State": "disabled"
                    },
                    "PublicDnsName": null,
                    "Platform": "windows",
                    "State": {
                        "Code": 0,
                        "Name": "pending"
                    },
                    "EbsOptimized": false,
                    "LaunchTime": "2013-07-19T02:42:39.000Z",
                    "PrivateIpAddress": "10.0.1.114",
                    "ProductCodes": [],
                    "VpcId": "vpc-1a2b3c4d",
                    "InstanceId": "i-5203422c",
                    "ImageId": "ami-173d747e",
                    "PrivateDnsName": ip-10-0-1-114.ec2.internal,
                    "KeyName": "MyKeyPair",
                    "SecurityGroups": [
                        {
                            "GroupName": "my-sg",
                            "GroupId": "sg-903004f8"
                        }
                    ],
                    "ClientToken": null,
                    "SubnetId": "subnet-6e7f829e",
                    "InstanceType": "t2.micro",
                    "NetworkInterfaces": [
                        {
                            "Status": "in-use",
                            "SourceDestCheck": true,
                            "VpcId": "vpc-1a2b3c4d",
                            "Description": "Primary network interface",
                            "NetworkInterfaceId": "eni-a7edb1c9",
                            "PrivateIpAddresses": [
                                {
                                    "PrivateDnsName": "ip-10-0-1-114.ec2.internal",
                                    "Primary": true,
                                    "PrivateIpAddress": "10.0.1.114"
                                }
                            ],
                            "PrivateDnsName": "ip-10-0-1-114.ec2.internal",
                            "Attachment": {
                                "Status": "attached",
                                "DeviceIndex": 0,
                                "DeleteOnTermination": true,
                                "AttachmentId": "eni-attach-52193138",
                                "AttachTime": "2013-07-19T02:42:39.000Z"
                            },
                            "Groups": [
                                {
                                    "GroupName": "my-sg",
                                    "GroupId": "sg-903004f8"
                                }
                            ],
                            "SubnetId": "subnet-6e7f829e",
                            "OwnerId": "123456789012",
                            "PrivateIpAddress": "10.0.1.114"
                        }              
                    ],
                    "SourceDestCheck": true,
                    "Placement": {
                        "Tenancy": "default",
                        "GroupName": null,
                        "AvailabilityZone": "us-west-2b"
                    },
                    "Hypervisor": "xen",
                    "BlockDeviceMappings": [
                        {
                            "DeviceName": "/dev/sda1",
                            "Ebs": {
                                "Status": "attached",
                                "DeleteOnTermination": true,
                                "VolumeId": "vol-877166c8",
                                "AttachTime": "2013-07-19T02:42:39.000Z"
                            }
                        }              
                    ],
                    "Architecture": "x86_64",
                    "StateReason": {
                        "Message": "pending",
                        "Code": "pending"
                    },
                    "RootDeviceName": "/dev/sda1",
                    "VirtualizationType": "hvm",
                    "RootDeviceType": "ebs",
                    "Tags": [
                        {
                            "Value": "MyInstance",
                            "Key": "Name"
                        }
                    ],
                    "AmiLaunchIndex": 0
                }
            ]
        }
######## EC2-Classic
The following command launches a t1.micro instance in EC2-Classic:

        aws ec2 run-instances --image-id ami-xxxxxxxx --count 1 --instance-type t1.micro --key-name MyKeyPair --security-groups my-sg
        {
            "OwnerId": "123456789012",
            "ReservationId": "r-5875ca20",
            "Groups": [
                {
                    "GroupName": "my-sg",
                    "GroupId": "sg-903004f8"
                }
            ],
            "Instances": [
                {
                    "Monitoring": {
                        "State": "disabled"
                    },
                    "PublicDnsName": null,
                    "Platform": "windows",
                    "State": {
                        "Code": 0,
                        "Name": "pending"
                    },
                    "EbsOptimized": false,
                    "LaunchTime": "2013-07-19T02:42:39.000Z",
                    "ProductCodes": [],
                    "InstanceId": "i-5203422c",
                    "ImageId": "ami-173d747e",
                    "PrivateDnsName": null,
                    "KeyName": "MyKeyPair",
                    "SecurityGroups": [
                        {
                            "GroupName": "my-sg",
                            "GroupId": "sg-903004f8"
                        }
                    ],
                    "ClientToken": null,
                    "InstanceType": "t1.micro",
                    "NetworkInterfaces": [],
                    "Placement": {
                        "Tenancy": "default",
                        "GroupName": null,
                        "AvailabilityZone": "us-west-2b"
                    },
                    "Hypervisor": "xen",
                    "BlockDeviceMappings": [
                        {
                            "DeviceName": "/dev/sda1",
                            "Ebs": {
                                "Status": "attached",
                                "DeleteOnTermination": true,
                                "VolumeId": "vol-877166c8",
                                "AttachTime": "2013-07-19T02:42:39.000Z"
                            }
                        }              
                    ],
                    "Architecture": "x86_64",
                    "StateReason": {
                        "Message": "pending",
                        "Code": "pending"
                    },
                    "RootDeviceName": "/dev/sda1",
                    "VirtualizationType": "hvm",
                    "RootDeviceType": "ebs",
                    "Tags": [
                        {
                            "Value": "MyInstance",
                            "Key": "Name"
                        }
                    ],
                    "AmiLaunchIndex": 0
                }
            ]
        }
####### Adding a Block Device Mapping to Your Instance
Each instance that you launch has an associated root device volume. You can use block device mapping to specify additional EBS volumes or instance store volumes to attach to an instance when it's launched.
To add a block device mapping to your instance, specify the `--block-device-mappings` option when you use `run-instances`.
The following example adds a standard Amazon EBS volume, mapped to `/dev/sdf`, that's 20 GB in size.
`--block-device-mappings "[{\"DeviceName\":\"/dev/sdf\",\"Ebs\":{\"VolumeSize\":20,\"DeleteOnTermination\":false}}]"`
The following example adds an Amazon EBS volume, mapped to `/dev/sdf`, based on a snapshot. When you  specify a snapshot, it isn't necessary to specify a volume size, but if you do, it must be greater or equal to the size of the snapshot.
`--block-device-mappings "[{\"DeviceName\":\"/dev/sdf\",\"Ebs\":{\"SnapshotId\":\"snap-xxxxxxxx\"}}]"`
The following example adds two instance store volumes. Note that the number of instance store volumes available to your instance depends on its instance type.
`--block-device-mappings "[{\"DeviceName\":\"/dev/sdf\",\"VirtualName\":\"ephemeral0\"},{\"DeviceName\":\"/dev/sdg\",\"VirtualName\":\"ephemeral1\"}]"`
The following example omits a mapping for a device specified by the AMI used to launch the instance (`/dev/sdj`):
`--block-device-mappings "[{\"DeviceName\":\"/dev/sdj\",\"NoDevice\":\"\"}]"`
For more information, see Block Device Mapping in the Amazon EC2 User Guide for Linux Instances.
####### Adding a Name Tag to Your Instance
To add the tag `Name=MyInstance` to your instance, use the `create-tags` commands as follows:
`aws ec2 create-tags --resources i-xxxxxxxxx --tags Key=Name,Value=MyInstance`
For more information, see Tagging Your Resources in the Amazon EC2 User Guide for Linux Instances.
####### Connecting to Your Instance
While your instance is running, you can connect to it and use it just as you'd use a computer sitting in front of you. For more information, see Connect to Your Amazon EC2 Instance in the Amazon EC2 User Guide for Linux Instances.
####### Listing Your Instances
You can use the AWS CLI to list your instances and view information about them. You can list all your instances, or filter the results based on the instances that you're interested in.
**Note**: Before you try the example commands, set your default credentials.
The following examples show how to use the `describe-instances` command.
**Example 1: List the instances with the specified instance type**
The following command lists your t2.micro instances.
`aws ec2 describe-instances --filters "Name=instance-type,Values=t2.micro" --query Reservations[].Instances[].InstanceId`
**Example 2: List the instances with the specified tag**
The following command lists the instances with a tag "Name=MyInstance".
`aws ec2 describe-instances --filters "Name=tag:Name,Values=MyInstance"`
**Example 3: List the instances launched using the specified images**
The following command lists your instances that were launched from the following AMIs: ami-x0123456,ami-y0123456,ami-z0123456.
`aws ec2 describe-instances --filters "Name=image-id,Values=ami-x0123456,ami=y0123456,ami-z0123456"`
####### Terminating Your Instance
Terminating an instance effectively deletes it; you can't reconnect to an instance after you've terminated it. As soon as the state of the instance changes to `shutting-down` or `terminated`, you stop incurring charges for that instance.
When you are finished with the instance, use the `terminate-instances` command as follows:

        aws ec2 terminate-instances --instance-ids i-5203422c
        {
          "TerminatingInstances":[
            {
              "InstanceId":"i-5203422c",
              "CurrentState":{
                "Code":32,
                "Name":"shutting-down"
              },
              "PreviousState":{
                "Code":16,
                "Name":"running"
              }
            }
          ]
        }
For more information, see Terminate Your Instance in the Amazon EC2 User Guide for Linux Instances.

##### Troubleshooting AWS CLI errors
After installing with `pip`, you may need to add the aws executable to your OS's PATH environment variable, or change its mode to make it executable.
###### **Error**: `aws: scommand not found`
You may need to add the aws executable to your OS's PATH environment variable.
If aws is in your PATH and you still see this error, you may no have the right file mode. Try running it directly.
`$ ~/.local/bin/aws --version`
###### Error: `permission denied`
Make sure that the aws script has a file mode that is executable. For example, 755.
Run `chmod +x` to make the file executable.
`$ chmod +x ~/.local/bin/aws`
###### Error: `AWS was not able to validate the provided credentials`
The AWS CLI may be reading credentials from a different location than you expect. Run `aws configure list` to confirm that the correct crednetials are used.

        $ aws configure list
        Name        Value       Type        Location
        ----        ----        ----        ----
        profile     <not set>   None        None
        access_key  \*********   XYVA        shared-credential-file
        secret_key  *********   ZAGY        shared-credential-file
        region      us-west-2   config-file ~/.aws/config

If the correct credentials are used, your clock may be out of sync. On Linux, macOS, or Unix, run `date` to check the time.
`date`
###### Error:`An error occurred (UnauthorizedOperation) when calling the CreateKeyPair operation: You are not authorized to perform this operation.
Your IAM user or role needs permission to call the API actions that correspond to the commands that you run with the AWS CLI. Most commands call a single action with a name that matches the command name; however, custom commands like `aws s3 sync` call multiple APIs. You can see which APIs a command calls by using the `--debug` option.
### User Guide for Linux Instances on Amazon EC2
#### [What Is Amazon EC2?](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/concepts.html)
##### Features of Amazon EC2
##### How to get started with Amazon EC2
##### Related Services
##### Accessing Amazon EC2
##### Pricing for Amazon EC2
##### [Instances and AMIs](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-instances-and-amis.html)
###### Instances
####### Storage for Your Instance
####### Security Best Practices
####### Stopping, Starting, and Terminating Instances
###### AMIs
##### [Regions and Availability Zones](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/using-regions-availability-zones.html)
###### Region and Availability Zone Concepts
####### Regions
####### Availability Zones
###### Available Regions
###### Regions and Endpoints
###### Describing Your Regions and Availability Zones
####### To find your regions and Availability Zones using the console
####### To find your regions and Availability Zones using the command line
###### Specifying the Region for a Resource
####### To specify the region for a resource using the console
####### To specify the default region using the environment
####### To specify the default region using the command line
###### Launching Instances in an Availability Zone
####### To specify an Availability Zone for your instance using the console
####### To specify an Availability Zone for your instance using the AWS CLI
####### To specify an Availability Zone for your instance using the AWS Tools for Windows PowerShell
###### Migrating an Instance to Another Availability Zone
##### [Amazon EC2 Root Device Volume](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/RootDeviceStorage.html)
###### Root Device Storage concepts
####### Instance Store-backed Instances
####### Amazon EBS-backed Instances
###### Choosing an AMI by Root Device Type
####### To choose an Amazon EBS-backed AMI using the console
####### To choose an instance store-backed AMI using the console
####### To verify the type of the root device volume of an AMI using the command line
###### Determining the Root Device Type of Your Instance
####### To determine the root device type of an instance using the console
####### To determine the root device type of an instance using the command line
###### Changing the Root Device Volume to Persist
####### To change the root device volume of an instance to persist at launch using the console
####### Changing the Root Volume of an Instance to Persist Using the AWS CLI
######## Example at Launch
######## Example While the Instance is Running
#### Setting Up with Amazon EC2
##### Sign Up for AWS
###### To create an AWS account
##### Create an IAM User
###### To create an IAM user for yourself and add the user to an Administrators group
##### Create a Key Pair
###### To create a key pair
###### To connect to your instance using your key pair
##### Create a Virtual Private Cloud (VPC)
##### Create a Security Group
#### Getting Started with Amazon EC2 Linux Instances
##### Overview
##### Prerequisites
##### Step 1: Launch an Instance
##### Step 2: Connect to Your Instance
##### Step 3: Clean Up Your Instance
##### Next Steps
* Learn how to remotely manage your EC2 instance using Run Command.
* Configure a CloudWatch alarm to notify you if your usage exceeds the Free Tier.
* Add an EBS volume.
* Install the LAMP stack.
#### [Best Practices for Amazon EC2](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-best-practices.html)
#### Amazon EC2 Instances
##### [Instance Types](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/instance-types.html)
###### Available Instance Types
####### Current Generation Instances
####### Previous Generation Instances
###### Hardware Specification
###### Virtualization Types
###### Networking and Storage Features
###### Instance Limits
###### Burstable Performance Instances
####### Hardware Specifications
####### Burstable Performance Instance Requirements
####### Best Practices
###### [CPU Credits and Baseline Performance](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/t2-credits-baseline-concepts.html)
####### [Unlimited Mode](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/t2-unlimited.html)
####### [Standard Mode](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/t2-std.html)
####### [Working with T2 and T3 Instances](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/t-how-to.html)
####### [Monitoring Your CPU Credits](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/t2-instances-monitoring-cpu-credits.html)
###### [General Purpose Instances](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/general-purpose-instances.html)
**M5 Instances**
**T3 Instances**
**T2 Instances**
####### Hardware Specifications
####### Instance Performance
####### Network Performance
####### Instance Features
####### Release Notes
###### [Compute Optimized Instances](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/compute-optimized-instances.html)
####### Hardware Specifications
###### [Memory Optimized Instances](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/memory-optimized-instances.html)
###### [Storage Optimized Instances](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/storage-optimized-instances.html)
###### [Linux Accelerated Computing Instances](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/accelerated-computing-instances.html)
####### Accelerated Computing Instance Families
######## F1 Instances
######## P3 Instances
######## P2 Instances
######## G3 Instances
######## G2 Instances
####### Hardware Specifications
####### Network Performance
####### Instance Features
####### Release Notes
####### AMIs for GPU-Based Accelerated Computing Instances
* [NVIDIA P3 AMIs](https://aws.amazon.com/marketplace/search/results/?page=1&filters=instance_types&instance_types=p3.2xlarge&searchTerms=NVIDIA)
* [NVIDIA P2 AMIs](https://aws.amazon.com/marketplace/search/results/?page=1&filters=instance_types&instance_types=p2.xlarge&searchTerms=NVIDIA)
You can also install the NVIDIA driver manually. For more information, see [Installing the NVIDIA Driver on Linux Instances](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/install-nvidia-driver.html)
####### [Installing the NVIDIA Driver on Linux Instances](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/install-nvidia-driver.html)
######## Uninstalling Amazon-provided NVIDIA packages
######## Downloading the NVIDIA GRID Driver (G3)
######## Downloading a Public NVIDIA Driver (G2, P2, P3)
######## Installing the NVIDIA Driver Manually
**To install the driver on a Linux instance**
####### [Activate NVIDIA GRID Virtual Applications (G3 Instances Only)](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/activate_grid.html)
####### [Optimizing GPU Settings (P2, P3, and G3 Instances)](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/optimize_gpu.html)
####### [Getting Started with FPGA Development](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/fpga-getting-started.html)
###### [T1 Micro Instances](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/concepts_micro_instances.html)
###### [Changing the Instance Type](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-instance-resize.html)
####### Compatibility for Resizing Instances
####### Resizing an Amazon EBS-backed Instance
####### Migrating to a New Instance Configuration
###### [Optimizing CPU Options](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/instance-optimize-cpu.html)
####### Rules for Specifying CPU Options
####### CPU Cores and Threads Per CPU Core Per Instance Type
####### Specifying CPU Options for Your Instance
######## To disable Intel Hyper-Threading Technology during instance launch
######## To specify a custom number of vCPUs during instance launch
####### Viewing the CPU Options for Your Instance
##### [Instance Purchasing Options](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/instance-purchasing-options.html)
###### Determining the Instance Lifecycle
####### To determine the instance lifecycle using the console
####### To determine the instance lifecycle using the AWS CLI
###### [Reserved Instances](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-reserved-instances.html)
####### Payment Options
####### Using Reserved Instances in a VPC
####### Reserved Instance Limits
###### [Scheduled Reserved Instances](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-scheduled-instances.html)
###### [Spot Instances](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/using-spot-instances.html)
####### Concepts
* Spot Instance pool
* Spot price
* Spot Instance request
* Spot Fleet
* Spot Instance interruption
####### How to Get Started
####### Pricing
* View Prices
* View Billing
####### [How Spot Instances Work](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/how-spot-instances-work.html)
######## Launching Spot Instances in a Launch Group
######## Launching Spot Instances in an Availability Zone Group
######## Launching Spot Instances in a VPC
####### [How Spot Fleet Works](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/spot-fleet.html)
######## On-Demand in Spot Fleet
######## Allocation Strategy for Spot Instances
* Maintaining Target Capacity
* Configuring Spot Fleet for Cost Optimization
* Configuring Spot Fleet or Cost Optimization and Diversification
* Choosing an Appropriate Allocation Strategy
######## Spot Price Overrides
######## Spot Fleet Instance Weighting
######## Walkthrough: Using Spot Fleet with Instance Weighting
####### [Spot Instance Pricing History](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/using-spot-instances-history.html)
######## To view the Spot price history using the console
######## To view the Spot price history using the command line
####### [Spot Instance Requests](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/spot-requests.html)
######## Spot Instance Request States
######## Specifying a Duration for Your Spot Instances
######## Specifying a Tenancy for Your Spot Instances
**To create the IAM role**
######## Creating a Spot Instance Request
* Prerequisites
* To create a Spot Instance request using the console
* To create a Spot Instance request using the AWS CLI
######## Finding Running Spot Instances
* To find running Spot Instances using the console
* To find running Spot Instances using the AWS CLI
######## Tagging Spot Instances Requests
* To add a tag to your Spot Instance request or Spot Instance using the AWS
######## Canceling a Spot Instance Request
######## [Spot Request Example Launch Specifications](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/spot-request-examples.html)
* Example 1: Launch Spot Instances
* Example 2: Launch Spot Instances in the Specified Availability Zone
* Example 3: Launch Spot Instances in the Specified Subnet
####### [Spot Fleet Requests](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/spot-fleet-requests.html)
######## Spot Fleet Request States
######## Spot Fleet Prerequisites
**To create the IAM role for Spot Fleet**
######## Spot Fleet and IAM Users
######## Spot Fleet Health Checks
######## Planning a Spot Fleet Request
######## Creating a Spot Fleet Request
* To create a Spot Fleet request using the console
* To create a Spot Fleet request using the AWS CLI
######## Monitoring Your Spot Fleet
* To monitor your Spot Fleet using the console
* To monitor your Spot Fleet using the AWS CLI
######## Modifying a Spot Fleet Request
* To modify a Spot Fleet request using the console
* To modify a Spot Fleet request using the AWS CLI
######## Canceling a Spot Fleet Request
* To cancel a Spot Fleet request using the console
* To cancel a Spot Fleet request using the AWS CLI
######## [Spot Fleet Example Configurations](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/spot-fleet-examples.html)
######## Example 1: Launch Spot Instances Using the Lowest-Priced Availability Zone or Subnet in the Region
######## Example 2: Launch Spot Instances Using the Lowest-Priced Availability Zone or Subnet in a Specified List
######## Example 3: Launch a Spot Instances Using the Lowest-Priced Instance Type in a Specified List
######## Example 4: Override the Price for the Request
######## Example 5: Launch a Spot Fleet Using the Diversified Allocation Strategy
######## Example 6: Launch a Spot Fleet Using the Instance Weighting
######## Example 7: Launch a Spot Fleet with On-Demand Capacity
####### [CloudWatch Metrics for Spot Fleet](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/spot-fleet-cloudwatch-metrics.html)
######## Spot Fleet Metrics
######## Spot Fleet Dimensions
######## View the ClouWatch Metrics for your Spot Fleet
####### [Automatic Scaling for Spot Fleet](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/spot-fleet-automatic-scaling.html)
####### [Spot Request Status](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/spot-bid-status.html)
######## Life Cycle of a Spot Request
######## Getting Request Status Information
* To get request status information using the console
* To get request status information using the command line
######## Spot Request Status Codes
####### [Spot Instance Interruptions](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/spot-interruptions.html)
######## Interruption Behavior
* Stopping Interrupted Spot Instances
* Hibernating Interrupted Spot Instances
######## Preparing for Interruptions
######## Preparing for Instance Hibernation
######## Spot Instance Interruption Notices
* EC2 Spot Instance Interruption Warning
* instance-action
* termination-time
####### [Spot Instance Data Feed](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/spot-data-feeds.html)
######## Data Feed File Name and Format
######## Amazon S3 Bucket Requirements
######## Subscribing to Your Spot Instance Data Feed
######## Deleting Your Spot Instance Data Feed
####### [Spot Instance Limits](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/using-spot-limits.html)
######## Spot Request Limits
######## Spot Fleet Limits
######## T2 Instances
##### [Instance Lifecycle](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-instance-lifecycle.html)
###### Instance Launch
###### Instance Stop and Start (Amazon EBS-Backed Instances Only)
###### Instance Reboot
###### Instance Retirement
###### Instance Termination
###### Differences Between Reboot, Stop, and Terminate
###### [Launch Your Instance](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/LaunchingAndUsingInstances.html)
####### [Launching an Instance Using the Launch Instance Wizard](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/launching-instance.html)
######## Launching Your Instance from an AMI
####### [Launching an Instance from a Launch Template](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-launch-templates.html)
######## Launch Template Restrictions
######## Using Launch Templates to Control Launch Parameters
######## Controlling the Use of Launch Templates
######## Creating a Launch Template
* To create a new launch template using the console
* To create a launch template from an existing launch template using the console
* To create a launch template using the command line
* To get instance data for a launch template using the command line
########  Managing Launch Template Versions
* Creating a Launch Template Version
    * To create a launch template version using the console
    * To create a launch template version using the command line
* Setting the Default Template Version
    * To set the default launch template version using the console
    * To set the default launch template version using the command line
* Deleting a Launch Template Version
    * To delete a launch template version using the console
    * To delete a launch template version using the command line
######## Launching an Instance from a Launch Template
* To launch an instance from a launch template using the console
* To launch an instance from a launch template using the command line
######## Using Launch templates with Amazon EC2 Auto Scaling
######## Using Launch Templates with EC2 Fleet
######## Using Launch Templates with Spot Fleet
######## Deleting a Launch Template
####### [Launching an Instance Using Parameters from an Existing Instance](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/launch-more-like-this.html)
####### [Launching a Linux Instance from a Backup](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/instance-launch-snapshot.html)
####### [Launching an AWS Marketplace Instance](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/launch-marketplace-console.html)
* To launch an instance from the AWS Marketplace using the launch wizard
* Launching an AWS Marketplace AMI Instance Using the API and CLI
####### [Launching an EC2 Fleet](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-fleet.html)
######## EC2 Fleet Limitations
######## [EC2 Fleet Configuration Strategies](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-fleet-configuration-strategies.html)
* Planning an EC2 Fleet
* EC2 Fleet Request Types
* Allocation Strategy for Spot Instance
    * Maintaining Target Capacity
    * Configuring EC2 Fleet for Cost Optimization
    * Configuring EC2 Fleet for Cost Optimization and Diversification
    * Choosing the Appropriate Allocation Strategy
* Configuring EC2 Fleet for On-Demand Backup
    * Prioritizing Instance Types for On-Demand Capacity
* Maximum Price Overrides
* EC2 Fleet Instance Weighting
* Walkthrough: Using EC2 Fleet with Instance Weighting
* Walkthrough: Using EC2 Fleet with On-Demand as the Primary Capacity
######## [Managing an EC2 Fleet](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/manage-ec2-fleet.html)
* EC2 Fleet Request States
* EC2 Fleet Prerequisites
* EC2 Fleet Health Checks
* Generating an EC2 Fleet JSON Configuration File
    * To generate a JSON file with all possible EC2 Fleet parameters using the command line
    * EC2 Fleet JSON Configuration File Reference
* Creating an EC2 Fleet
* Tagging an EC2 Fleet
* Monitoring Your EC2 Fleet
    * To monitor your EC2 Fleet using the AWS CLI
* Modifying an EC2 Fleet
* Deleting an EC2 Fleet
* [EC2 Fleet Example Configuration](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-fleet-examples.html)
    * Example 1: Launch Spot Instances as the Default Purchasing Model
    * Example 2: Launch On-Demand Instances as the Default Purchasing Model
    * Example 3: Launch On-Demand Instances as the Primary Capacity
    * Example 4: Launch Spot Instances Using the Lowest Price Allocation Strategy
###### [Connect to Your Linux Instance](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/AccessingInstances.html)
####### [Connecting to Your Linux Instance Using SSH](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/AccessingInstancesLinux.html)
######## Prerequisites
######## Connecting to Your Linux Instance
######## Transferring Files to Linux Instances from Linux Using SCP
###### [Stop and Start Your Instance](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/Stop_Start.html)
####### Overview
####### Stopping and Starting Your Instances
* To stop and start an Amazon EBS-backed instance using the console
* To stop and start an Amazon EBS-backed instance using the command line
    * [Stop-instances](https://docs.aws.amazon.com/cli/latest/reference/ec2/stop-instances.html)
####### Modifying a Stopped Instance
* To modify an instance attribute
* To modify an instance attribute using the command line
    * [modify-instance-attribute](https://docs.aws.amazon.com/cli/latest/reference/ec2/modify-instance-attribute.html)
####### Troubleshooting
###### [Reboot Your Instance](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-instance-reboot.html)
* To reboot an instance using the console
* To reboot an instance using the command line
    * [reboot-instances](https://docs.aws.amazon.com/cli/latest/reference/ec2/reboot-instances.html)
###### [Instance Retirement](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/instance-retirement.html)
####### Identifying Instances Scheduled for Retirement
* To identify instances scheduled for retirement using the console
* To identify instances scheduled for retirement using the command line
    * [describe-instance-status](https://docs.aws.amazon.com/cli/latest/reference/ec2/describe-instance-status.html#describe-instance-status)
####### Working with Instances Scheduled for Retirement
* Determining Your Instance Root Device Type
    * To determine your instance root device type using the console
    * To determine your instance root device type using the command line
        * [describe-instances](https://docs.aws.amazon.com/cli/latest/reference/ec2/describe-instances.html)
* Managing Instances Scheduled for Retirement
###### [Terminate Your Instance](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/terminating-instances.html)
####### Instance Termination
####### Terminating an Instance
* To terminate an instance using the console
* To terminate an instance using the command line
    * [terminate-instances](https://docs.aws.amazon.com/cli/latest/reference/ec2/terminate-instances.html)
####### Enabling Termination Protection for an Instance
* Limits
* To enable termination protection for an instance at launch time
* To enable termination protection for a running or stopped instance
* To disable termination protection fora running or stopped instance
* To enable or disable termination protection using the command line
    * [modify-instance-attribute](https://docs.aws.amazon.com/cli/latest/reference/ec2/modify-instance-attribute.html)
####### Changing the Instance Initiated Shutdown Behavior
* To change the shutdown behavior of an instance using the console
* To change the shutdown behavior of an instance using the command line
####### Preserving Amazon EBS Volumes on Instance Termination
* To change the root volume of an instance to persist at launch using the console
* Changing the Root Volume to Persist at Launch Using the Command Line
* Changing the Root Volume of a Running Instance to Persist Using the Command Line
####### Troubleshooting
###### [Recover Your Instance](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-instance-recover.html)
##### [Configure Instances](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/Configure_Instance.html)
###### Common Configuration Scenarios
###### [Managing Software on Your Linux Instance](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/managing-software.html)
####### [Updating Instance Software](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/install-updates.html)
####### [Adding Repositories](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/add-repositories.html)
####### [Finding Software Packages](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/find-software.html)
####### [Installing Software Packages](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/install-software.html)
####### [Preparing to Compile Software](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/compile-software.html)
###### [Managing User Accounts on Your Linux Instance](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/managing-users.html)
* To add a user account
* To remove a user from the system
###### [Processor State Control for Your EC2 Instance](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/processor_state_control.html)
####### Highest Performance with Maximum Turbo Boost Frequency
####### High Performance and Low Latency by Limiting Deeper C-states
* To limit deeper sleep states on Amazon Linux 2
* To limit deeper states on Amazon Linux AMI
####### Baseline Performance with the Lowest Variability
* To limit deeper sleep states and disable Turbo Boost on Amazon Linux 2
* To limit deeper sleep states and disable Turbo Boost on Amazon Linux AMI
###### [Setting the Time for Your Linux Instance](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/set-time.html)
####### Configuring the Amazon Time Sync Service on Amazon Linux AMI
####### Configuring the Amazon Time Sync Service on Ubuntu
####### Configuring the Amazon Time Sync Service on SUSE Linux
####### Changing the Time Zone on Amazon Linux
###### [Changing the Hostname of Your Linux Instance](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/set-hostname.html)
* To change the system hostname to a public DNS name
* To change the system hostname without a public DNS name
####### Changing the Shell Prompt Without Affecting the Hostname
####### Changing the Hostname on Other Linux Distributions
###### [Setting Up Dynamic DNS on Your Linux Instance](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/dynamic-dns.html)
###### [Running Commands on Your Linux Instance at Launch](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/user-data.html)
####### Prerequisites
####### User Data and Shell Scripts
####### User Data and the Console
* Specify Instance User Data at Launch
* View and Update the Instance User Data
####### User Data and cloud-init Directives
* To pass cloud-init directives to an instance with user data
####### User Data and the AWS CLI
* Example: Specify User Data at Launch
* Example: Modify the User Data of a Stopped Instance
* Example: View User Data
###### [Instance Metadata and User Data](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-instance-metadata.html)
####### Retrieving Instance Metadata
* Examples of Retrieving Instance Metadata
####### Working with Instance User Data
* Specify Instance User Data at Launch
* Modify Instance User Data
* Retrieve Instance User Data
####### Retrieving Dynamic Data
####### Example: AMI Launch Index Value
####### Instance Metadata Categories
####### [Instance Identity Documents](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/instance-identity-documents.html)
* Obtaining the Instance Identity Document and Signatures
* Verifying the PKCS7 Signature
##### [Identify EC2 Linux Instances](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/identify_ec2_instances.html)
###### Inspecting the System UUID
###### Inspecting the Instance Identity Document
#### [Monitoring](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/monitoring_ec2.html)
#### [Network and Security](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/EC2_Network_and_Security.html)
##### [Amazon EC2 Key Pairs](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-key-pairs.html)
* Creating a Key Pair
* Launching and Connecting to Your Instance
* Key Pairs for Multiple Users
###### Creating a Key Pair Using Amazon EC2
* To create your key pair using the Amazon EC2 console
* To create your key pair using the command line
    * [create-key-pair](https://docs.aws.amazon.com/cli/latest/reference/ec2/create-key-pair.html)
###### Importing Your Own Public Key to Amazon EC2
* To create a key pair using a third-party tool
* To import the public key
* To import the public key using the command line
    * [import-key-pair](https://docs.aws.amazon.com/cli/latest/reference/ec2/import-key-pair.html)
* To verify that your key pair was imported
* To view your key pair using the command line
    * [describe-key-pairs](https://docs.aws.amazon.com/cli/latest/reference/ec2/describe-key-pairs.html)
###### Retrieving the Public Key for Your Key Pair on Linux
###### Retrieving the Public Key for Your Key Pair From Your Instance
###### Verifying Your Key Pair's Fingerprint
###### Deleting Your Key Pair
* To delete your key pair using the console
* To delete you key pair using the command line
    * [delete-key-pair](https://docs.aws.amazon.com/cli/latest/reference/ec2/delete-key-pair.html)
###### Adding or Replacing a Key Pair for Your Instance
###### Connecting to Your Linux Instance if You Lose Your Private Key
##### [Amazon EC2 Security Groups for Linux Instances](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/using-network-security.html)
###### Security Groups for EC2-Classic
###### Security Groups for EC2-VPC
###### Security Group Rules
* Connection Tracking
###### Default Security Groups
###### Custom Security Groups
###### Working with Security Groups
* Creating a Security Group
    * To create a new security group using the console
    * To create a security group using the command line
        * [create-security-group](https://docs.aws.amazon.com/cli/latest/reference/ec2/create-security-group.html)
    * To copy a security group using the console
    * [EC2-VPC] To modify the security groups for an instance using the command line
        * [modify-instance-attribute](https://docs.aws.amazon.com/cli/latest/reference/ec2/modify-instance-attribute.html)
    * To describe your security groups for EC2-Classic using the console
    * To describe you security groups for EC2-VPC using the console
        * [describe-security-groups](https://docs.aws.amazon.com/cli/latest/reference/ec2/describe-security-groups.html)
* Adding Rules to a Security Group
    * To add rules to a security group using the console
    * To add one or more ingress rules to a security group using the command line
        * [authorize-security-group-ingress](https://docs.aws.amazon.com/cli/latest/reference/ec2/authorize-security-group-ingress.html)
    * [EC2-VPC] To add one or more egress rules to a security group using the command line
        * [authorize-security-group-egress](https://docs.aws.amazon.com/cli/latest/reference/ec2/authorize-security-group-egress.html)
* Updating Security Groups Rules
    * To update a security group rule using the console
    * To update the description for an ingress security group rule using the command line
        * [update-security-group-rule-descriptions-ingress](https://docs.aws.amazon.com/cli/latest/reference/ec2/update-security-group-rule-descriptions-ingress.html)
    * [EC2-VPC] To update the description for an egress security group rule using the command line
        * [update-security-group-rule-descriptions-egress](https://docs.aws.amazon.com/cli/latest/reference/ec2/update-security-group-rule-descriptions-egress.html)
* Deleting Rules from a Security Group
    * To delete a security group rule using the console
    * To remove one or more ingress rules from a security group using the command line
        * [revoke-security-group-ingress](https://docs.aws.amazon.com/cli/latest/reference/ec2/revoke-security-group-ingress.html)
    * [EC2-VPC] To remove one or more egress rules from a security group using the command line
        * [revoke-security-group-egress](https://docs.aws.amazon.com/cli/latest/reference/ec2/revoke-security-group-egress.html)
* Deleting a Security Group
    * To delete a security group using the console
    * To delete a security group using the command line
        * [delete-security-group](https://docs.aws.amazon.com/cli/latest/reference/ec2/delete-security-group.html)
###### [Security Group Rules Reference](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/security-group-rules-reference.html)
##### [Controlling Access to Amazon EC2 Resources](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/UsingIAM.html)
* Network Access to Your Instance
* Amazon EC2 Permission Attributes
* IAM and Amazon EC2
    * Creating an IAM Group and Users
        * To create an IAM group
        * To create an IAM user, add the user to your group, and create a password for the user
###### [IAM Policies for Amazon EC2](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/iam-policies-for-amazon-ec2.html)
* Getting started
####### [Policy Structure](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/iam-policy-structure.html)
* Policy Syntax
* Actions for Amazon EC2
* Amazon Resource Names for Amazon EC2
* Condition Keys for Amazon EC2
* Checking That Users Have the Required Permissions
####### [Supported Resource-Level Permissions for Amazon EC2 API Actions](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-supported-iam-actions-resources.html)
####### [Example Policies for Working with the AWS CLI or an AWS SDK](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ExamplePolicies_EC2.html)
* 1: Read-Only Access
* 2: Restricting Access to a Specific Region
* 3: Working with Instances
    * Describe, Launch, Stop, Start, and Terminate All Instances
    * Describe All Instances, and Stop, Start, and Terminate Only Particular Instances
* 4: Working with Volumes
    * Attaching and Detaching Volumes
    * Creating a Volume
    * Creating a Volume with Tags
* 5: Working with Snapshots
    * Creating a Snapshot
    * Creating a Snapshot with Tags
    * Modifying Permissions Settings for Snapshot
* 6: Launching Instances (RunInstances)
    * AMI
    * Instance Type
    * Subnet
    * EBS Volumes
    * Applying Tags
    * Applying Tags in a Launch Template
    * Attaching an Elastic GPU
    * Launch Templates
* 7: Working with Reserved Instances
* 8: Tagging Resources
* 9: Working with IAM Roles
* 10: Working with Route Tables
* 11: Allowing a Specific Instance to View Resources in Other AWS Services
* 12: Working with Launch Templates
####### [Example Policies for Working in the Amazon EC2 Console](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/iam-policies-ec2-console.html)
* 1: Read-Only Access
    * a. View instances, AMIs, and Snapshots
    * b. View instances and CloudWatch metrics
* 2: Using the EC2 Launch Wizard
    * a. Basic launch wizard access
    * b. Restrict access to specific instance type, subnet, and region
* 3: Working with Volumes
* 4: Working with Security Groups
    * a. View security groups and add and remove rules
    * b. Working with the Create Security Group dialog box
* 5: Working with Elastic IP Address
* 6: Working with Reserved Instances
###### [IAM Roles for Amazon EC2](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/iam-roles-for-amazon-ec2.html)
####### Instance Profiles
* [Using Instance Profiles](https://docs.aws.amazon.com/IAM/latest/UserGuide/id_roles_use_switch-role-ec2_instance-profiles.html)
    * Managing Instance Profiles (Console)
    * Managing Instance Profiles (AWS CLI or AWS API)
####### Retrieving Security Credentials from Instance Metadata
####### Granting an IAM User Permission to Pass an IAM Role to an Instance
####### Working with IAM Roles
* Creating an IAM Role
    * To create an IAM role using the IAM console
    * To create an IAM role and instance profile using the AWS CLI
* Launching an Instance with an IAM Role
    * To launch an instance with an IAM role using the console
    * To launch an instance with an IAM role using the AWS CLI
* Attaching an IAM Role to an Instance
    * To attach an IAM role to an instance using the console
    * To attach an IAM role to an instance using the AWS CLI
* Detaching an IAM Role
    * To detach an IAM role from an instance using the console
    * To detach an IAM role from an instance using the AWS CLI
* Replacing an IAM Role
    * To replace an IAM role for an instance using the console
    * To replace an IAM role for an instance using the AWS CLI
###### [Network Access: Authorizing Inbound Traffic for Your Linux Instances](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/authorizing-access-to-an-instance.html)
####### Before You Start
####### Adding a Rule for Inbound SSH Traffic to a Linux Instance
* To add a rule to a security group for inbound SSH traffic over IPv4 using the console
* To add a rule to a security group for inbound SSH traffic over IPv6 using the console
* To add a rule to a security group using the command line
####### Assigning a Security Group to an Instance
##### [Instance IP Addressing](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/using-instance-addressing.html)
###### Private IPv4 Addresses and Internal DNS Hostnames
###### Public IPv4 Addresses and External DNS Hostnames
###### Elastic IP Addresses (IPv4)
###### Amazon DNS Server
###### IPv6 Addresses
###### Working with IP Addresses for Your Instance
* Determining Your Public, Private and Elastic IP Addresses
    * To determine your instance's private IPv4 addresses using the console
    * To determine your instance's public IPv4 addresses using the console
    * To determine your instance's IPv4 addresses using instance metadata
* Determining Your IPv6 Addresses
    * To determine your instance's IPv6 addresses using the console
    * To determine your instance's IPv6 addresses using instance metadata
* Assigning a Public IPv4 Address During Instance Launch
    * To access the public IP addressing feature when you launching an instance
    * To enable or disable the public IP addressing feature using the command line
* Assigning an IPv6 Address to an Instance
    * To assign an IPv6 address to an instance during launch
    * To assign an IPv6 address to an instance after launch
    * To assign an IPv6 address to an instance using the command line
* Unassigning an IPv6 address from an instance
    * To unassign an IPv6 address from an instance
    * To unassign an IPv6 address using the command line
###### [Multiple IP Addresses](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/MultipleIP.html)
* How Multiple IP Addresses Work
* Working with Multiple IPv4 Addresses
    * Assigning a Secondary Private IPv4 Address
        * To assign a secondary private IPv4 address when launching an instance
        * To assign a secondary IPv4 address during launch using the command line
        * To assign a secondary private IPv4 address to a network interface
        * To assign a secondary private IPv4 address to an existing instance using the command line
    * Configuring the Operating System on Your Instance to Recognize the Secondary Private IPv4 Address
    * Associating an Elastic IP Address with the Secondary Private IPv4 Address
        * To associate an Elastic IP address with a secondary private IPv4 address
        * To associate an Elastic IP address with a secondary private IPv4 address using the command line
    * Viewing Your Secondary Private IPv4 Address
        * To view the private IPv4 addresses assigned to a network interface
        * To view the private IPv4 addresses assigned to an instance
    * Unassigning a Secondary Private IPv4 Address
        * To unassign a secondary private IPv4 address from an instance
        * To unassign a secondary private IPv4 address from a network interface
        * To unassign a secondary private IPv4 address using the command line
* Working with Multiple IPv6 Addresses
    * Assigning Multiple IPv6 Addresses
        * To assign multiple IPv6 addresses during launch
        * To assign multiple IPv6 addresses to an existing instance
        * To assign multiple IPv6 addresses to a network interface
        * CLI overview
            * Assign an IPv6 address during launch
            * Assign an IPv6 address to a network interface
    * Viewing Your IPv6 Addresses
        * To view the IPv6 addresses assigned to an instance
        * To view the IPv6 addresses assigned to a network interface
        * CLI overview
            * View the IPv6 addresses for an instance
            * View the IPv6 addresses for a network interface
    * Unassigning an IPv6 Address
        * To unassign an IPv6 address from an instance
        * To unassign an IPv6 address from a network interface
        * CLI Overview
            * `unassign-ipv6-addresses`
##### [Elastic IP Addresses](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/elastic-ip-addresses-eip.html)
###### Elastic Elastic IP address basics
我们知道公网IP其实就是你的服务器在网络上的家，如果你的家总是搬朋友很容易就找不到你的。AWS会每一个实例分配一个公网IP，但是不固定，如果要固定一个IP，我们就要申请一个弹性IP。
Action注意 AWS的弹性IP分配政策是非常有意思的，申请一个IP是免费的，但空闲是收费的。你申请的IP必须绑定在一个正在运行的实例上，否则按照0.05USD每小时收费。我就因为将一个实例关机一晚上而产生了0.5USD的账单。
###### Working with Elastic IP Addresses
* Allocating an Elastic IP Address
    * To allocate an Elastic IP Address using the console
    * To allocate an Elastic IP Address using the command line
* Describing Your Elastic IP Addresses
    * To describe your Elastic IP Addresses using the console
    * To describe your Elastic IP Addresses using the command line
* Tagging an Elastic IP Address
    * To tag an Elastic IP address using the console
    * To tag an Elastic IP address using the command line
        * [`create-tags`](https://docs.aws.amazon.com/cli/latest/reference/ec2/create-tags.html)
* Associating an Elastic Address with a Running Instance
    * To associate an Elastic IP address with an instance using the console
    * To associate an Elastic IP address using the command line
        * [`associate-address`](https://docs.aws.amazon.com/cli/latest/reference/ec2/associate-address.html)
* Disassociating an Elastic IP Address and Reassociating with a Different Instance
    * To disassociate and reassociate an Elastic IP address using the console
    * To disassociate an Elastic IP address using the command line
        * [`disassociate-address`](https://docs.aws.amazon.com/cli/latest/reference/ec2/disassociate-address.html)
    * To associate an Elastic IP address using the command line
        * [`associate-address`](https://docs.aws.amazon.com/cli/latest/reference/ec2/associate-address.html)
* Releasing an Elastic IP Address
    * To release an Elastic IP Address using the console
    * To release an Elastic IP Address using the command line
        * [`release-address`](https://docs.aws.amazon.com/cli/latest/reference/ec2/release-address.html)
* Recovering an Elastic IP Address
    * To recover an Elastic IP address using the command line
###### Using Reverse DNS for Email Applications
###### Elastic IP Address Limit
##### [Elastic Network Interfaces](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/using-eni.html)
###### Network Interface Basics
* Public IPv4 addresses for network interfaces
* IPv6 addresses for network interfaces
* Monitoring IP Traffic
###### IP Addresses Per Network Interface Per Instance Type
###### Scenarios for Network Interfaces
* Creating a Management Network
* Use Network and Security Appliances in Your VPC
* Creating Dual-homed Instances with Workloads/Roles on Distinct Subnets
* Create a Low Budget High Availability Solution
###### Best Practices for Configuring Network Interfaces
###### Working with Network Interfaces
* Creating a Network Interface
    * To create a network interface using the console
    * To create a network interface using the command line
        * [`create-network-interface`](https://docs.aws.amazon.com/cli/latest/reference/ec2/create-network-interface.html)
* Deleting a network interface
    * To delete a network interface using the console
    * To delete a network interface using the command line
        * [`delete-network-interface`](https://docs.aws.amazon.com/cli/latest/reference/ec2/delete-network-interface.html)
* Viewing Details about a Network Interface
    * To describe a network interface using the console
    * To describe a network interface using the command line
        * [`describe-network-interfaces`](https://docs.aws.amazon.com/cli/latest/reference/ec2/describe-network-interfaces.html)
* Attaching a Network Interface When Launching an Instance
    * To attach a network interface when launching an instance using the console
    * To attach a network interface when launching an instance using the command line
        * [`run-instances`](https://docs.aws.amazon.com/cli/latest/reference/ec2/run-instances.html)
* Attaching a Network Interface to a Stopped or Running Instance
    * To attach a network interface to an instance using the Instances page
    * To attach a network interface to an instance using the Network Interfaces page
    * To attach a network interface to an instance using the command line
        * [`attach-network-interface`](https://docs.aws.amazon.com/cli/latest/reference/ec2/attach-network-interface.html)
* Detaching a Network Interface from an Instance
    * To detach a network interface from an instance using the Instances page
    * To detach a network interface from an instance using the Network Interfaces page
    * To detach a network interface using the command line
        * [`detach-network-interface`](https://docs.aws.amazon.com/cli/latest/reference/ec2/detach-network-interface.html)
* Changing the Security Group
    * To change the security group of a network interface using the console
    * To change the security group of a network interface using the command line
        * [`modify-network-interface-attribut`](https://docs.aws.amazon.com/cli/latest/reference/ec2/modify-network-interface-attribute.html)
* Changing the Source or Destination Checking
    * To change the source/destination checking for a network interface using the console
    * To change the source/destination checking for a network interface using the command line
        * [`modify-network-interface-attribute`](https://docs.aws.amazon.com/cli/latest/reference/ec2/modify-network-interface-attribute.html)
* Associating an Elastic IP Address (IPv4)
    * To associate an Elastic IP address using the command line
    * To associate an Elastic IP address using the command line
        * [`associate-address`](https://docs.aws.amazon.com/cli/latest/reference/ec2/associate-address.html)
* Disassociating an Elastic IP Address (IPv4)
    * To disassociate an Elastic IP Address using the console
    * To disassociate an Elastic IP Address using the command line
        * [`disassociate-address`](https://docs.aws.amazon.com/cli/latest/reference/ec2/disassociate-address.html)
* Assigning an IPv6 Address
    * To assign an IPv6 address to a network interface using the console
    * To assign an IPv6 address to a network interface using the command line
        * [`assign-ipv6-addresses`](https://docs.aws.amazon.com/cli/latest/reference/ec2/assign-ipv6-addresses.html)
* Unassigning an IPv6 Address
    * To unassign an IPv6 address from a network interface using the console
    * To unassign an IPv6 address from a network interface using the command line
        * [`unassign-ipv6-addresses`](https://docs.aws.amazon.com/cli/latest/reference/ec2/unassign-ipv6-addresses.html)
* Changing Termination Behavior
    * To change the termination behavior for a network interface using the console
    * To change the termination behavior for a network interface using the command line
        * [`modify-network-interface-attribute`](https://docs.aws.amazon.com/cli/latest/reference/ec2/modify-network-interface-attribute.html)
* Adding or Editing a Description
    * To change the description for a network interface using the console
    * To change the description for a network interface using the command line
        * [`modify-network-interface-attribute`](https://docs.aws.amazon.com/cli/latest/reference/ec2/modify-network-interface-attribute.html)
* Adding or Editing Tags
    * To add or edit tags for a network interface using the console
    * To add or edit tags for a network interface using the command line
        * [`create-tags`](https://docs.aws.amazon.com/cli/latest/reference/ec2/create-tags.html)
###### [Requester-Managed Network Interfaces](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/requester-managed-eni.html)
##### [Enhanced Networking on Linux](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/enhanced-networking.html)
###### Enhanced Networking Types
###### Enabling Enhanced Networking on Your Instance
###### [Enabling Enhanced Networking with the Intel 82599 VF Interface on Linux Instances](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/sriov-networking.html)
* Requirements
* Testing Whether Enhanced Networking is Enabled
    * Instance Attribute (sriovNetSupport)
        * [`describe-instance-attribute`](https://docs.aws.amazon.com/cli/latest/reference/ec2/describe-instance-attribute.html)
        * `aws ec2 describe-instance-attribute --instance-id instance_id --attribute sriovNetSupport`
    * Image Attribute (sriovNetSupport)
        * [`describe-image-attribute`](https://docs.aws.amazon.com/cli/latest/reference/ec2/describe-image-attribute.html)
        * `aws ec2 describe-image-attribute --image-id ami_id --attribute sriovNetSupport`
    * Network Interface Driver (`ixgbevf`)
        * `ethtool -i eth0`
* Enabling Enhanced Networking on Amazon Linux
    * To enable enhanced networking
    * To enable enhanced networking (instance store-backed instances)
* Enabling Enhanced Networking on Ubuntu
    * To install the linux-aws kernel package
* Enabling Enhanced Networking on Other Linux Distributions
###### [Enabling Enhanced Networking with the Elastic Network Adapter (ENA) on Linux Instances](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/enhanced-networking-ena.html)
* Requirements
* Testing Whether Enhanced Networking is Enabled
    * Kernel Module (ena)
        * `modinfo ena`
    * Instance Attribute (enaSupport)
        * `aws ec2 describe-instances --instance-ids instance_id --query "Reservations[].Instances[].EnaSupport"`
    * Image Attribure (enaSupport)
        * `aws ec2 describe-images --image-id ami_id --query "Images[].EnaSupport"`
    * Network Interface Driver
        * `ethtool -i eth0`
* Enabling Enhanced Networking on the Amazon Linux AMI
    * To enable enhanced networking on Amazon Linux AMI
    * To enable enhanced networking on Amazon Linux AMI (instance store-backed instances)
* Enabling Enhanced Networking on Ubuntu
    * To install the linux-aws kernel package
* Enabling Enhanced Networking on Linux
###### [Troubleshooting the Elastic Network Adapter](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/troubleshooting-ena.html)
* Troubleshooting Connectivity Issues
    * To disable enhanced networking with ENA (EBS-backed instances)
    * To disable enhanced networking with ENA (instance store-backed instances)
* Keep-Alive Mechanism
* Register Read Timeout
* Statistics
* Driver Error Logs in syslog
##### [Placement Groups](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/placement-groups.html)
###### Cluster Placement Groups
###### Spread Placement Groups
###### Placement Group Rules and Limitations
###### Creating a Placement Group
* To create a placement group using the console
* To create a placement group using the command line
    * [`create-placement-group`](https://docs.aws.amazon.com/cli/latest/reference/ec2/create-placement-group.html)
###### Launching Instances in a Placement Group
* To launch instances into a placement group using the console
* To launch instances into a placement group using the command line
    * 1. Create an AMI for your instances using the following command:
        * [`create-image`](https://docs.aws.amazon.com/cli/latest/reference/ec2/create-image.html)
    * 2. Launch instances into your placement group using the following command:
        * `--placement` with `run-instances`
###### Changing the Placement Group for an Instance
* To move an instance to a placement group using the command line
    * 1. Stop the instance using the following command:
        * [`stop-instances`](https://docs.aws.amazon.com/cli/latest/reference/ec2/stop-instances.html)
    * 2. Use the `modify-instance-placement` command to specify the name of the placement group to which to move the instance.
        * `aws ec2 modify-instance-placement --instance-id i-0aa51192b00939a40 --group-name MySpreadGroup`
    * 3. Restart the instance using the following command
        * [`start-instances`](https://docs.aws.amazon.com/cli/latest/reference/ec2/start-instances.html)
* To remove an instance from a placement group using the command line
###### Deleting a placement group
* To terminate or move instances and delete a placement group using the console
* To terminate instances and delete a placement group using the command line
##### [Network Maximum Transmission Unit (MTU) for Your EC2 Instance](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/network_mtu.html)
###### Jumbo Frames (9001 MTU)
###### Path MTU Discovery
###### Check the Path MTU Between Two Hosts
* To check path MTU using tracepath
###### Check and Set the MTU on Your Linux Instance
* To check the MTU setting on a Linux instance
* To set the MTU value on a Linux instance
##### [Virtual Private Clouds](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/using-vpc.html)
#### [VPC](https://docs.aws.amazon.com/vpc/latest/userguide/what-is-amazon-vpc.html)
##### [What is Amazon VPC](https://docs.aws.amazon.com/vpc/latest/userguide/what-is-amazon-vpc.html)
###### Amazon EC2 Concepts
* VPCs and Subnets
* Supported Platforms
* Default and Nondefault VPCs
* Accessing the internet
* Accessing a Corporate or Home Network
* Accessing Services Through AWS PrivateLink
###### How to Get Started with Amazon VPC
###### Accessing Amazon VPC
###### Pricing for Amazon VPC
###### Amazon VPC Limits
###### PCI DSS Compliance
##### [Getting Started with Amazon VPC](https://docs.aws.amazon.com/vpc/latest/userguide/vpc-getting-started.html)
###### [Getting Started with IPv4 for Amazon VPC](https://docs.aws.amazon.com/vpc/latest/userguide/getting-started-ipv4.html)
* Step 1: Create the VPC
    * To create a VPC using the Amazon VPC Wizard
    * Viewing Information About Your VPC
* Step 2: Create a Security Group
    * Rules for the WebServerSG Security Group
    * Creating Your WebServerSG Security Group
* Step 3: Launch an Instance into Your VPC
* Step 4: Assign an Elastic IP Address to Your Instance
* Step 5: Clean up
###### [Getting Started with IPv6 for Amazon VPC](https://docs.aws.amazon.com/vpc/latest/userguide/get-started-ipv6.html)
* Step 1: Create the VPC
    * To create a VPC using the Amazon VPC wizard
    * Viewing information About Your VPC
* Step 2: Create a Security Group
    * Rules for the WebServerSG Security Group
    * Creating Your WebServerSG Security Group
* Step 3: Launch an Instance
##### [Scenarios and Examples](https://docs.aws.amazon.com/vpc/latest/userguide/VPC_Scenarios.html)
##### [VPCs and Subnets](https://docs.aws.amazon.com/vpc/latest/userguide/VPC_Subnets.html)
###### VPC and Subnet Basics
###### VPC and Subnet Sizing
* VPC and Subnet Sizing for IPv4
* Adding IPv4 CIDR Blocks to a VPC
* VPC and Subnet Sizing for IPv6
###### Subnet Routing
* [Route Tables](https://docs.aws.amazon.com/vpc/latest/userguide/VPC_Route_Tables.html)
* [NAT](https://docs.aws.amazon.com/vpc/latest/userguide/vpc-nat.html)
###### Subnet Security
* [Network ACLs](https://docs.aws.amazon.com/vpc/latest/userguide/vpc-network-acls.html)
###### Connections with Your Local Network and Other VPCs
##### [IP Addressing](https://docs.aws.amazon.com/vpc/latest/userguide/vpc-ip-addressing.html)
* Private IPv4 Addresses
* Public IPv4 Addresses
* IPv6 Addresses
* IP Addressing Behavior for Your Subnet
* Working with IP Addresses
    * Modifying the Public IPv4 Addressing Attribute for Your Subnet
    * Modifying the IPv6 Addressing Attribute for Your Subnet
    * Assigning a Public IPv4 Address During Instance Launch
    * Assigning an IPv6 Address During Instance Launch
    * Assigning an IPv6 Address to an Instance
    * Unassigning an IPv6 Address From an Instance
    * API and Command Overview
##### [VPN Connections](https://docs.aws.amazon.com/vpc/latest/userguide/vpn-connections.html)
###### [AWS Managed VPN Connections](https://docs.aws.amazon.com/vpc/latest/userguide/VPC_VPN.html)
#### [Storage](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/Storage.html)
* Amazon EBS
* Amazon EC2 Instance Store
* Amazon EFS File System
* Amazon S3
* Adding Storage
