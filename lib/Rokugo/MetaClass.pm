package Rokugo::MetaClass;
use strict;
use warnings;
use utf8;
use 5.010_001;
use Sub::Identify qw();

# DO NOT CALL THIS METHOD DIRECTLY.
sub new {
    my $class = shift;
    my %args = @_==1 ? %{$_[0]} : @_;
    my $self = bless {%args}, $class;
    $self;
}

sub methods {
    my $self = shift;
    no strict 'refs';

    my @ret;
    my $klass = $self->{name};
    my %hash = %{"${klass}::"};
    while (my ($k, $v) = each %hash) {
        next if $k =~ /^(?:BEGIN|CHECK|END)$/;
        next unless *{"${klass}::${k}"}{CODE};
        next if $klass ne Sub::Identify::stash_name($klass->can($k));
        push @ret, $k;
    }
    return @ret;
}

1;
