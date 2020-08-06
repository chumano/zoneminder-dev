package ONVIF::Media::Types::ReverseOptions;
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

my %Mode_of :ATTR(:get<Mode>);
my %Extension_of :ATTR(:get<Extension>);

__PACKAGE__->_factory(
    [ qw(        Mode
        Extension

    ) ],
    {
        'Mode' => \%Mode_of,
        'Extension' => \%Extension_of,
    },
    {
        'Mode' => 'ONVIF::Media::Types::ReverseMode',
        'Extension' => 'ONVIF::Media::Types::ReverseOptionsExtension',
    },
    {

        'Mode' => 'Mode',
        'Extension' => 'Extension',
    }
);

} # end BLOCK








1;


=pod

=head1 NAME

ONVIF::Media::Types::ReverseOptions

=head1 DESCRIPTION

Perl data type class for the XML Schema defined complexType
ReverseOptions from the namespace http://www.onvif.org/ver10/schema.






=head2 PROPERTIES

The following properties may be accessed using get_PROPERTY / set_PROPERTY
methods:

=over

=item * Mode


=item * Extension




=back


=head1 METHODS

=head2 new

Constructor. The following data structure may be passed to new():

 { # ONVIF::Media::Types::ReverseOptions
   Mode => $some_value, # ReverseMode
   Extension =>  { # ONVIF::Media::Types::ReverseOptionsExtension
   },
 },




=head1 AUTHOR

Generated by SOAP::WSDL

=cut

