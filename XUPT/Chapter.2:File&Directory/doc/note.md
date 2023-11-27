`ls -ail`

`-` regular file

`d` directory file
`c` character device file
`b` block device file
`p` pipe file
`s` socket file
`l` link file

访问权限: owner->owner group->other

`open(const char *path, int flags, mode_t mode);`≈`fopen(const char *filename, const char *mode);`+`chmod(const char *filename, mode_t mode)`

