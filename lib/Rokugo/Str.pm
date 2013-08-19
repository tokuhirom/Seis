package Rokugo::Str;
use strict;
use warnings;
use utf8;
use 5.012_001;
use Data::Dumper ();
use feature 'fc';

sub uc:method { CORE::uc($_[0]) }
sub lc:method { CORE::lc($_[0]) }
sub fc:method { CORE::fc($_[0]) }
sub ord:method { CORE::ord($_[0]) }

sub say { CORE::say($_[0]) }

sub perl {
    local $Data::Dumper::Terse = 1;
    local $Data::Dumper::Useqq = 1;
    local $Data::Dumper::Purity = 1;
    local $Data::Dumper::Indent = 0;
    Data::Dumper::Dumper($_[0]);
}

sub clone { "$_[0]" }

sub Bool { boolean::boolean($_[0]) }

sub lines {
    my ($self, $n) = @_;
    my @lines = split /\n/, $self;
    $n ? [@lines[0..$n-1]] : \@lines;
}

# Generate new IO object.
# IO.new(ins => 0, chomp => Bool::True, path => "/tmp/")
sub IO {
    if (@_==1) {
        Rokugo::IO->_new($_[0]);
    } else {
        ...
    }
}

sub defined { 1 }

1;

