ran_lib_common_sources = files('''
    context.c
'''.split())

#ran_lib_common_inc = include_directories('.')

ran_lib_common = library('ogsran-common',
    sources : ran_lib_common_sources,
    include_directories : [libcore_inc, libinc],
    dependencies : [threads, librt, libexecinfo, libsocket, libtalloc_dep, libcore_dep]
)

#ran_lib_common_dep = declare_dependency(
#    link_with : ran_lib_common,
#    include_directories : [libcore_inc, libinc, ran_lib_common_inc],
#    dependencies : [threads, librt, libexecinfo, libsocket, libtalloc_dep, libcore_dep, ran_src_dep]
#)

