package ONVIF::Device::Types::RelativeFocusOptions;
use strict;
use warnings;


__PACKAGE__->_set_element_form_qualified(1);

sub get_xmlns { 'http://www.onvif.org/ver10/schema' };

our $XML_ATTRIBUTE_CLASS;
undef $XML_ATTRIBUTE_CLASS;

sub __get_attr_class {
    return $XML_ATTRIBUTE_CLASS;
}

use Class::Std::Fast::Storable constructor => 'none';
use base qw(SOAP::WSDL::XSD::Typelib::ComplexType);

Class::Std::initialize();

{ # BLOCK to scope variables

my %Distance_of :ATTR(:get<Distance>);
my %Speed_of :ATTR(:get<Speed>);

__PACKAGE__->_factory(
    [ qw(        Distance
        Speed

    ) ],
    {
        'Distance' => \%Distance_of,
        'Speed' => \%Speed_of,
    },
    {
        'Distance' => 'ONVIF::Device::Types::FloatRange',
        'Speed' => 'ONVIF::Device::Types::FloatRange',
    },
    {

        'Distance' => 'Distance',
        'Speed' => 'Speed',
    }
);

} # end BLOCK








1;


=pod

=head1 NAME

ONVIF::Device::Types::RelativeFocusOptions

=head1 DESCRIPTION

Perl data type class for the XML Schema defined complexType
RelativeFocusOptions from the namespace http://www.onvif.org/ver10/schema.






=head2 PROPERTIES

The following properties may be accessed using get_PROPERTY / set_PROPERTY
methods:

=over

=item * Distance


=item * Speed




=back


=head1 METHODS

=head2 new

Constructor. The following data structure may be passed to new():

 { # ONVIF::Device::Types::RelativeFocusOptions
   Distance =>  { # ONVIF::Device::Types::FloatRange
     Min =>  $some_value, # float
     Max =>  $some_value, # float
   },
   Speed =>  { # ONVIF::Device::Types::FloatRange
     Min =>  $some_value, # float
     Max =>  $some_value, # float
   },
 },




=head1 AUTHOR

Generated by SOAP::WSDL

=cut

