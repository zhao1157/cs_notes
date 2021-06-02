set tabstop=4
set shiftwidth=4
set expandtab
filetype indent on

autocmd BufWinLeave *.* mkview
autocmd BufWinEnter *.* silent loadview

set number
set hls

set mouse=a
