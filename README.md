# Full-text-search
## Intoduction
Full-Text Search is a software tool developed in the C++ language.
## Installation project
Clone the repository to your local machine:

      git clone https://github.com/your-username/full-text-search
      cd full-text-search

Update git submodules:

      git submodule init
      git submodule add

Generate and bulding project using presets:

      cmake --preset release
      cmake --build --preset release

## Usage

1. Example of indexing:

       ./build/release/bin/fts index --csv books.csv --index index

2. Example of searching:

       ./build/release/bin/fts search --index index

You can view the full list of subcommands and options using:

        ./build/release/bin/fts --help-all
