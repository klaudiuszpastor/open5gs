ran_src_sources = files('''
    rrc_establishment.c
    rrc_reconfiguration.c
    rach_procedure.c
'''.split())

#ran_src_inc = include_directories('.')

ran_src = library('ogsran-src',
    sources : ran_src_sources,
    # include_directories : [ran_src_inc],
    dependencies : [threads, librt, libexecinfo, libsocket, libtalloc_dep, libcore_dep]
)

#ran_src_dep = declare_dependency(
#    link_with : ran_src,
#    include_directories : ran_src_inc,
#    dependencies : [threads, librt, libexecinfo, libsocket, libtalloc_dep, libcore_dep]
#)

