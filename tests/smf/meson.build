testunit_unit_sources = files('''
    abts-main.c
    smf-bearer-tft-update-test.c
'''.split())

testunit_unit_exe = executable('smf_tests',
  sources: testunit_unit_sources,
  c_args : testunit_core_cc_flags, 
  include_directories : [libtestapp_inc, srcinc, libinc, libtestcommon_inc, testinc],
  dependencies : [libsmf_dep])


test('smf_tests', testunit_unit_exe, is_parallel: false, suite: 'smf')