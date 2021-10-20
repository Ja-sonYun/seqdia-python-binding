from distutils.core import setup, Extension

seqdia_module = Extension(
    'seqdia',
    [
        'seqdia.c',
        '../grammars/arrow_connection.c',
        '../grammars/participant.c',
        '../renderer.c',
        '../parser.c',
        '../scanner.c',
        '../style.c'
    ],
    define_macros=[('PYTHON_BINDING', '1')],
)

seqdia_headers = ["../parser.h"]

setup(name='seqdia', ext_modules=[seqdia_module], headers=seqdia_headers)
