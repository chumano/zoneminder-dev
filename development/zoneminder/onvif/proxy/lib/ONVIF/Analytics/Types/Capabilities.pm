package ONVIF::Analytics::Types::Capabilities;
use strict;
use warnings;


__PACKAGE__->_set_element_form_qualified(1);

sub get_xmlns { 'http://www.onvif.org/ver20/analytics/wsdl' };

our $XML_ATTRIBUTE_CLASS = 'ONVIF::Analytics::Types::Capabilities::_Capabilities::XmlAttr';

sub __get_attr_class {
    return $XML_ATTRIBUTE_CLASS;
}

use Class::Std::Fast::Storable constructor => 'none';
use base qw(SOAP::WSDL::XSD::Typelib::ComplexType);

Class::Std::initialize();

{ # BLOCK to scope variables


__PACKAGE__->_factory(
    [ qw(
    ) ],
    {
    },
    {
    },
    {

    }
);

} # end BLOCK




package ONVIF::Analytics::Types::Capabilities::_Capabilities::XmlAttr;
use base qw(SOAP::WSDL::XSD::Typelib::AttributeSet);

{ # BLOCK to scope variables

my %RuleSupport_of :ATTR(:get<RuleSupport>);
my %AnalyticsModuleSupport_of :ATTR(:get<AnalyticsModuleSupport>);
my %CellBasedSceneDescriptionSupported_of :ATTR(:get<CellBasedSceneDescriptionSupported>);

__PACKAGE__->_factory(
    [ qw(
        RuleSupport
        AnalyticsModuleSupport
        CellBasedSceneDescriptionSupported
    ) ],
    {

        RuleSupport => \%RuleSupport_of,

        AnalyticsModuleSupport => \%AnalyticsModuleSupport_of,

        CellBasedSceneDescriptionSupported => \%CellBasedSceneDescriptionSupported_of,
    },
    {
        RuleSupport => 'SOAP::WSDL::XSD::Typelib::Builtin::boolean',
        AnalyticsModuleSupport => 'SOAP::WSDL::XSD::Typelib::Builtin::boolean',
        CellBasedSceneDescriptionSupported => 'SOAP::WSDL::XSD::Typelib::Builtin::boolean',
    }
);

} # end BLOCK




1;


=pod

=head1 NAME

ONVIF::Analytics::Types::Capabilities

=head1 DESCRIPTION

Perl data type class for the XML Schema defined complexType
Capabilities from the namespace http://www.onvif.org/ver20/analytics/wsdl.






=head2 PROPERTIES

The following properties may be accessed using get_PROPERTY / set_PROPERTY
methods:

=over



=back


=head1 METHODS

=head2 new

Constructor. The following data structure may be passed to new():

 { # ONVIF::Analytics::Types::Capabilities
 },



=head2 attr

NOTE: Attribute documentation is experimental, and may be inaccurate.
See the correspondent WSDL/XML Schema if in question.

This class has additional attributes, accessibly via the C<attr()> method.

attr() returns an object of the class ONVIF::Analytics::Types::Capabilities::_Capabilities::XmlAttr.

The following attributes can be accessed on this object via the corresponding
get_/set_ methods:

=over

=item * RuleSupport

 Indication that the device supports the rules interface and the rules syntax.



This attribute is of type L<SOAP::WSDL::XSD::Typelib::Builtin::boolean|SOAP::WSDL::XSD::Typelib::Builtin::boolean>.

=item * AnalyticsModuleSupport

 Indication that the device supports the scene analytics module interface.



This attribute is of type L<SOAP::WSDL::XSD::Typelib::Builtin::boolean|SOAP::WSDL::XSD::Typelib::Builtin::boolean>.

=item * CellBasedSceneDescriptionSupported

 Indication that the device produces the cell based scene description



This attribute is of type L<SOAP::WSDL::XSD::Typelib::Builtin::boolean|SOAP::WSDL::XSD::Typelib::Builtin::boolean>.


=back




=head1 AUTHOR

Generated by SOAP::WSDL

=cut

