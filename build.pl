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
my $alternative  = 0;
my $build        = 0;
my $test         = 0;
my $verbose      = 0;
my $output_dir   = 'build';
my $inv          = 0;

GetOptions(
    "alternative"  => \$alternative,
    "build"        => \$build,
    "test"         => \$test,
    "verbose"      => \$verbose,
    "output_dir=s" => \$output_dir,
    "inv"          => \$inv
) or die("Error in command line arguments\n");

# Ensure the output directory is set
$output_dir = File::Spec->rel2abs($output_dir);  # Convert to absolute path for consistency

# Define CMake arguments based on flags
my @cmake_args;
if ($alternative) 
{
   @cmake_args = ("-DALTERNATIVE=ON");
}
else
{
   @cmake_args = ("-DALTERNATIVE=OFF");  #just to be sure
}

if($verbose)
{
   my $extra_arg = "-DVERBOSE=ON";
   @cmake_args = map { $_ . " " . $extra_arg } @cmake_args;
}
else
{
   my $extra_arg = "-DVERBOSE=OFF";
   @cmake_args = map { $_ . " " . $extra_arg } @cmake_args;
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

if ($test) {
   if ($inv)
   {
       print "Running tests inversed\n";
       system("./AutisticAssembler/test/test_asm") == 0 or warn("Failed to run tests for ASM: $!\n");
       system("./ProcessorModel/test/test") == 0 or warn("Failed to run tests for CPU: $!\n");
   }
   else
   {
       print "Running tests\n";
       system("./ProcessorModel/test/test") == 0 or warn("Failed to run tests for CPU: $!\n");
       system("./AutisticAssembler/test/test_asm") == 0 or warn("Failed to run tests for ASM: $!\n");
   }
}


print color('magenta'),"Build and post-build steps completed successfully.\n", color('reset'), "\n";

