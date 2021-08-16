if [[ $# -eq 0 ]] ; then
    echo 'INSUFFICIENT INPUT ARGS:'
    echo '  usage:'
    echo '      source scriptname.sh start -> launch database server'
    echo '      source scriptname.sh stop -> close database server'
    return
fi

pg_ctl -D /usr/local/var/postgres $1
