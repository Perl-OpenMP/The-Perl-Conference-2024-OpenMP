use strict;
use warnings;

use OpenMP::Simple;
use OpenMP::Environment;

use Inline (
    C    => 'DATA',
    with => qw/OpenMP::Simple/,
);

my $env = OpenMP::Environment->new;

for my $num_threads ( 1 .. 16 ) {
    my $current_value = $env->omp_num_threads($num_threads);
    my $got_threads = run_tasks();
}

__DATA__
__C__
int run_tasks() {
    int got_num_threads = 0;
    PerlOMP_UPDATE_WITH_ENV__NUM_THREADS
    #pragma omp parallel
    {
        got_num_threads = omp_get_num_threads();
        #pragma omp single     // Ensure only one thread creates the initial task
        {
          #pragma omp task
          {printf("Perl ");}   // Task #1 
          #pragma omp task
          {printf("rocks ");} // Task #2
          #pragma omp task
          {printf("on %d threads!\n", got_num_threads);} // Task #3
          #pragma omp taskwait
        }
    }
    return got_num_threads;
}

__END__
