coding_sources = files('''
    decoding.c
    encoding.c
'''.split())

coding = library('coding',
    sources : coding_sources,
    c_args : '-DCODING_COMPILATION',
    include_directories : [libcore_inc, libinc],
    dependencies : [threads, librt, libexecinfo, libsocket, libtalloc_dep, libcore_dep])
