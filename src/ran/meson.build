ran_src = files('''
    rrc_establishment.c
    rrc_reconfiguration.c
'''.split())

ran = library('coding',
    sources : ran_src,
    c_args : '-DRAN_SRC_COMPILATION',
    include_directories : [libcore_inc, libinc],
    dependencies : [threads, librt, libexecinfo, libsocket, libtalloc_dep, libcore_dep])
