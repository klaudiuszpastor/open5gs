ran_lib_common = files('''
    context.c
    ogs-ran-common.c
'''.split())

ran_lib = library('coding',
    sources : ran_lib_common,
    c_args : '-DRAN_LIB_COMPILATION',
    include_directories : [libcore_inc, libinc],
    dependencies : [threads, librt, libexecinfo, libsocket, libtalloc_dep, libcore_dep])
