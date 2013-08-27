#! ./blib/script/seis
use v6;

use Test;

plan 14;

=begin desc

Pair list a la L<"http://www.nntp.perl.org/group/perl.perl6.language/19360">

=end desc

# L<S32::Containers/Array/=item pairs>

my $list = (1 => (2 => (3 => 4)));
isa_ok($list, Pair);

is($list.key, 1, 'the key is 1');
isa_ok($list.value, Pair, '$list.value is-a Pair');
is($list.value.key, 2, 'the list.value.key is 2');
isa_ok($list.value.value, Pair, '$list.value.value is-a Pair');
is($list.value.value.key, 3, 'the list.value.value.key is 3');
is($list.value.value.value, 4, 'the list.value.value.value is 4');

is($list, 1 => 2 => 3 => 4, 'pair operator nests right-associatively');

#?pugs todo
is($list.perl, '1 => 2 => 3 => 4', 'right-associative nested pairs .perl correctly');

my $r-list = (((1 => 2) => 3) => 4);

is($r-list.key, (1 => 2) => 3, 'the key is a nested pair');
is($r-list.key.key, 1 => 2, 'the key of the key is a nested pair');
is($r-list.value, 4, 'the value is a number');
is($r-list.key.value, 3, 'the value of the key is a number');

#?pugs todo
is($r-list.perl, '((1 => 2) => 3) => 4', 'key-nested pairs .perl correctly');

# vim: ft=perl6
