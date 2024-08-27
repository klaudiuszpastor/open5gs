test_crc_sources = files('''
    abts-main.c
    crc-decoding-tests.c
    crc-encoding-tests.c
'''.split())

testunit_unit_exe = executable('crc_tests',
    sources : test_crc_sources,
    c_args : testunit_core_cc_flags, 
    include_directories : [libcore_inc, libinc, libtestapp_inc, srcinc, libtestcommon_inc, testinc],
    dependencies : libcore_dep,
    link_with : coding)

test('crc_tests', testunit_unit_exe, is_parallel: false, suite: 'crc')



