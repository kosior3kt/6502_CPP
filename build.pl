#!/usr/bin/perl

use strict;
use warnings;
use Getopt::Long;
use File::Basename;
use File::Path qw(make_path);  # Ensure this module is imported
use Cwd qw(cwd);
use File::Spec;
use Term::ANSIColor;

# Command-line flags
my $experimental = 0;
my $build        = 0;
my $run          = 0;
my $test         = 0;
my $output_dir   = 'build';

GetOptions(
    "experimental" => \$experimental,
    "build"        => \$build,
    "run"          => \$run,
    "test"         => \$test,
    "output_dir=s" => \$output_dir,
) or die("Error in command line arguments\n");

# Ensure the output directory is set
$output_dir = File::Spec->rel2abs($output_dir);  # Convert to absolute path for consistency

# Define CMake arguments based on flags
my @cmake_args;
if ($build) {
   @cmake_args = ("-DBUILD_TEST=ON");
}
else {
   @cmake_args = ("-DBUILD_TEST=OFF");
}

# Create build directory if it does not exist
unless (-d $output_dir) {
    print color('magenta'), "Creating build directory: $output_dir\n", color('reset'), "\n";
    make_path($output_dir) or die("Failed to create build directory: $!\n");
}

# Run CMake
print color('magenta'), "Running cmake with arguments: @cmake_args\n", color('reset'), "\n";
my $cmake_command = "cmake .. -DCMAKE_BUILD_TYPE=Debug @cmake_args";

#this allows to run build command from root of the directory
chdir($output_dir) or die("Failed to change directory to $output_dir: $!\n");

system($cmake_command) == 0 or die("Failed to run cmake: $!\n");

# Optionally build
if ($build) {
   my $make_command = "make -j8";
   system($make_command) == 0 or die("Failed to run make: $!\n");
}

# Run optional post-build steps
if ($run) {
    print "Running ./src/dupa\n";
    system("./src/dupa") == 0 or warn("Failed to run ./src/dupa: $!\n");
}

if ($test) {
    print "Running ./test/test\n";
    system("./test/test") == 0 or warn("Failed to run ./test/test: $!\n");
}

print color('magenta'),"Build and post-build steps completed successfully.\n", color('reset'), "\n";

