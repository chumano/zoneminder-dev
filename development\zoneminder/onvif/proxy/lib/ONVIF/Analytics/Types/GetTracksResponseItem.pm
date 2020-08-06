package ONVIF::Analytics::Types::GetTracksResponseItem;
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

my %TrackToken_of :ATTR(:get<TrackToken>);
my %Configuration_of :ATTR(:get<Configuration>);

__PACKAGE__->_factory(
    [ qw(        TrackToken
        Configuration

    ) ],
    {
        'TrackToken' => \%TrackToken_of,
        'Configuration' => \%Configuration_of,
    },
    {
        'TrackToken' => 'ONVIF::Analytics::Types::TrackReference',
        'Configuration' => 'ONVIF::Analytics::Types::TrackConfiguration',
    },
    {

        'TrackToken' => 'TrackToken',
        'Configuration' => 'Configuration',
    }
);

} # end BLOCK








1;


=pod

=head1 NAME

ONVIF::Analytics::Types::GetTracksResponseItem

=head1 DESCRIPTION

Perl data type class for the XML Schema defined complexType
GetTracksResponseItem from the namespace http://www.onvif.org/ver10/schema.






=head2 PROPERTIES

The following properties may be accessed using get_PROPERTY / set_PROPERTY
methods:

=over

=item * TrackToken


=item * Configuration




=back


=head1 METHODS

=head2 new

Constructor. The following data structure may be passed to new():

 { # ONVIF::Analytics::Types::GetTracksResponseItem
   TrackToken => $some_value, # TrackReference
   Configuration =>  { # ONVIF::Analytics::Types::TrackConfiguration
     TrackType => $some_value, # TrackType
     Description => $some_value, # Description
   },
 },




=head1 AUTHOR

Generated by SOAP::WSDL

=cut

