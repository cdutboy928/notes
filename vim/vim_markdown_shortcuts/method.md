  * vim markdown shortcuts (check the mkdx.vim and the markdown-shortcuts)
      * **method1 (through plugin)**
          * vmap <leader>b <plugin>(command)
          * ftplugin
              `command! MarkdownToggleBold :call mdshortcuts#ToggleMultipleCharactersAroundWord(2, '*')`
          * autoload
              * functions
                   * visual mode
                   * count number
                   * I
                   * insert string (\* or \*\*)
                   * esc
                   * move right count
                   * a
                   * append string (\* or \*\*)
                   * esc
       * **method2** (function in `.vimrc`)
           * invoke
               `:nmap ;s :source /full/path/to/the/scriptfile.vim<CR>`
               or
               `:nmap \b :call MyBackupFunc(expand('%'), { 'all': 1 })<CR>`
           * functions (`scriptfile.vim)
                * visual mode
                * count number
                * I
                * insert string (\* or \*\*)
                * esc
                * move right count
                * a
                * append string (\* or \*\*)
                * esc
