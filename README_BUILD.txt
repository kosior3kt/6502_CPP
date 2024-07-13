If you want to build this project, you have two options:
    1. use existing perl script. It uses perl 5 and has some avaiable flags.
        --build             => builds thing (by default only thing script does is creating make files)
        --run               => runs it
        --test              => runs tests as well
        --experimental      => runs experimental version of code and tests (tests are the same ones, just not all of them)
        --output_dir=<name> => allows user to specify custom output dir (by default it is 'build')
    2. run cmakes yourself.
        Only thing which is not conventional is usage of -DBUILD_TEST={ON | OFF} flag. if you want to get experimental code and test turn this flag ON, else you can just ignore it.

Project structure:
    bin is in       <REPO_ROOT>/build/src/. It is called 'dupa'
    test is in      <REPO_ROOT>/build/test/. It is called 'test'    (duh...)

