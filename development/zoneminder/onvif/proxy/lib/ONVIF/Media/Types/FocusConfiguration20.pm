package ONVIF::Media::Types::FocusConfiguration20;
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

my %AutoFocusMode_of :ATTR(:get<AutoFocusMode>);
my %DefaultSpeed_of :ATTR(:get<DefaultSpeed>);
my %NearLimit_of :ATTR(:get<NearLimit>);
my %FarLimit_of :ATTR(:get<FarLimit>);
my %Extension_of :ATTR(:get<Extension>);

__PACKAGE__->_factory(
    [ qw(        AutoFocusMode
        DefaultSpeed
        NearLimit
        FarLimit
        Extension

    ) ],
    {
        'AutoFocusMode' => \%AutoFocusMode_of,
        'DefaultSpeed' => \%DefaultSpeed_of,
        'NearLimit' => \%NearLimit_of,
        'FarLimit' => \%FarLimit_of,
        'Extension' => \%Extension_of,
    },
    {
        'AutoFocusMode' => 'ONVIF::Media::Types::AutoFocusMode',
        'DefaultSpeed' => 'SOAP::WSDL::XSD::Typelib::Builtin::float',
        'NearLimit' => 'SOAP::WSDL::XSD::Typelib::Builtin::float',
        'FarLimit' => 'SOAP::WSDL::XSD::Typelib::Builtin::float',
        'Extension' => 'ONVIF::Media::Types::FocusConfiguration20Extension',
    },
    {

        'AutoFocusMode' => 'AutoFocusMode',
        'DefaultSpeed' => 'DefaultSpeed',
        'NearLimit' => 'NearLimit',
        'FarLimit' => 'FarLimit',
        'Extension' => 'Extension',
    }
);

} # end BLOCK








1;


=pod

=head1 NAME

ONVIF::Media::Types::FocusConfiguration20

=head1 DESCRIPTION

Perl data type class for the XML Schema defined complexType
FocusConfiguration20 from the namespace http://www.onvif.org/ver10/schema.






=head2 PROPERTIES

The following properties may be accessed using get_PROPERTY / set_PROPERTY
methods:

=over

=item * AutoFocusMode


=item * DefaultSpeed


=item * NearLimit


=item * FarLimit


=item * Extension




=back


=head1 METHODS

=head2 new

Constructor. The following data structure may be passed to new():

 { # ONVIF::Media::Types::FocusConfiguration20
   AutoFocusMode => $some_value, # AutoFocusMode
   DefaultSpeed =>  $some_value, # float
   NearLimit =>  $some_value, # float
   FarLimit =>  $some_value, # float
   Extension =>  { # ONVIF::Media::Types::FocusConfiguration20Extension
   },
 },




=head1 AUTHOR

Generated by SOAP::WSDL

=cut

