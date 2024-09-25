# RACH procedure tests

testunit_unit_sources = files('''
    abts-main.c
    rach-test.c
'''.split())

testunit_unit_exe = executable('rach_tests',
  sources: [testunit_unit_sources, ran_lib_common_sources,ran_src_sources],
  c_args : testunit_core_cc_flags, 
  include_directories : [libtestapp_inc, srcinc, libinc, libtestcommon_inc, testinc, libcore_inc],
  dependencies : [threads, librt, libexecinfo, libsocket, libtalloc_dep, libcore_dep]
)

  test('rach_tests', testunit_unit_exe, is_parallel: false, suite: 'rach')
