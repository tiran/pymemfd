# Copyright (c) 2016 Christian Heimes
# The MIT License (MIT)
# see LICENSE for details

import sys
import unittest

import memfd


class PyMemFDTests(unittest.TestCase):
    def test_simple(self):
        f = memfd.open('demo', flags=memfd.MFD_ALLOW_SEALING)
        self.assertEqual(f.name, 'memfd:demo')
        self.assertEqual(memfd.getseals(f), 0)
        f.write(b'hello world')
        f.seek(0)
        self.assertEqual(f.read(), b'hello world')
        memfd.addseals(f, memfd.F_SEAL_WRITE)
        self.assertEqual(memfd.getseals(f), memfd.F_SEAL_WRITE)
        with self.assertRaises(PermissionError):
            f.write(b'hello world')


def test_main():
    suite = unittest.TestSuite()
    suite.addTests(unittest.makeSuite(PyMemFDTests))
    return suite


if __name__ == "__main__":
    result = unittest.TextTestRunner(verbosity=2).run(test_main())
    sys.exit(not result.wasSuccessful())
