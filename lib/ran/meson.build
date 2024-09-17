ran_sources = files('''
    context.c
'''.split())

ran = library('coding',
    sources : ran_sources,
    c_args : '-DRAN_COMPILATION',
    include_directories : [libcore_inc, libinc],
    dependencies : [threads, librt, libexecinfo, libsocket, libtalloc_dep, libcore_dep])
