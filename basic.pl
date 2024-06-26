use strict;
use warnings;

use OpenMP::Simple;
use OpenMP::Environment;
use Test::More tests => 8;

use Inline (
    C    => 'DATA',
    with => qw/OpenMP::Simple/,
);

my $env = OpenMP::Environment->new;

for my $num_threads ( 1 .. 8 ) {
    my $current_value = $env->omp_num_threads($num_threads);
    is _get_num_threads(),$num_threads,
       sprintf qq{The number of threads (%0d) spawned in the OpenMP runtime via OMP_NUM_THREADS, as expected}, $num_threads;
}

__DATA__
__C__
int _get_num_threads() {
  PerlOMP_UPDATE_WITH_ENV__NUM_THREADS
  int ret = 0;
  #pragma omp parallel
  {
    #pragma omp single // first thread to reach here runs it, no others
    ret = omp_get_num_threads();
  }
  return ret;
}

__END__
