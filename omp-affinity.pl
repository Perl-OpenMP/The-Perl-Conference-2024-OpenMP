use strict;
use warnings;

use OpenMP::Simple;
use OpenMP::Environment;

use Inline (
    C    => 'DATA',
    with => qw/OpenMP::Simple/,
);

my $env = OpenMP::Environment->new;

foreach my $policy (qw/true close spread master false/) {
  for my $num_threads ( 1 .. 16 ) {
    my $current_value  = $env->omp_num_threads($num_threads);
    my $current_policy = $env->omp_proc_bind($policy);
    my $got_threads = runit();
  }
}

__DATA__
__C__
int runit() {
    PerlOMP_UPDATE_WITH_ENV__NUM_THREADS
    // Start a parallel region
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        printf("Thread %d is running on CPU %d\n", thread_id, sched_getcpu());
    }

    return 0;
}

__END__
