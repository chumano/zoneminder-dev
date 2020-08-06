package ONVIF::Media::Types::AnalyticsDeviceCapabilities;
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

my %XAddr_of :ATTR(:get<XAddr>);
my %RuleSupport_of :ATTR(:get<RuleSupport>);
my %Extension_of :ATTR(:get<Extension>);

__PACKAGE__->_factory(
    [ qw(        XAddr
        RuleSupport
        Extension

    ) ],
    {
        'XAddr' => \%XAddr_of,
        'RuleSupport' => \%RuleSupport_of,
        'Extension' => \%Extension_of,
    },
    {
        'XAddr' => 'SOAP::WSDL::XSD::Typelib::Builtin::anyURI',
        'RuleSupport' => 'SOAP::WSDL::XSD::Typelib::Builtin::boolean',
        'Extension' => 'ONVIF::Media::Types::AnalyticsDeviceExtension',
    },
    {

        'XAddr' => 'XAddr',
        'RuleSupport' => 'RuleSupport',
        'Extension' => 'Extension',
    }
);

} # end BLOCK








1;


=pod

=head1 NAME

ONVIF::Media::Types::AnalyticsDeviceCapabilities

=head1 DESCRIPTION

Perl data type class for the XML Schema defined complexType
AnalyticsDeviceCapabilities from the namespace http://www.onvif.org/ver10/schema.






=head2 PROPERTIES

The following properties may be accessed using get_PROPERTY / set_PROPERTY
methods:

=over

=item * XAddr


=item * RuleSupport


=item * Extension




=back


=head1 METHODS

=head2 new

Constructor. The following data structure may be passed to new():

 { # ONVIF::Media::Types::AnalyticsDeviceCapabilities
   XAddr =>  $some_value, # anyURI
   RuleSupport =>  $some_value, # boolean
   Extension =>  { # ONVIF::Media::Types::AnalyticsDeviceExtension
   },
 },




=head1 AUTHOR

Generated by SOAP::WSDL

=cut

