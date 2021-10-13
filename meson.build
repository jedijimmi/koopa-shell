project('koopa-shell', 'c')


inc = [
    include_directories('src')
]

src = ['example/main.c', 'src/koopa_shell.c']


executable('koopa-shell-example',
           src,
           include_directories: inc,
           link_args : '/FORCE:MULTIPLE'
)
