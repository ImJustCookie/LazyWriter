from setuptools import setup, find_packages

setup(
    name="lazywriter",
    version="0.2",
    packages=find_packages(),
    install_requires=[
        "PyQt6",
        "pynput"
    ],
    entry_points={
        'console_scripts': [
            'lazywriter = lazy_writer_raphael_senellart.main:main',  # This sets the entry point
        ],
    },
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    python_requires='>=3.6',
)
