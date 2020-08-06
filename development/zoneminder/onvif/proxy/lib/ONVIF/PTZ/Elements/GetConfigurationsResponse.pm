
package ONVIF::PTZ::Elements::GetConfigurationsResponse;
use strict;
use warnings;

{ # BLOCK to scope variables

sub get_xmlns { 'http://www.onvif.org/ver20/ptz/wsdl' }

__PACKAGE__->__set_name('GetConfigurationsResponse');
__PACKAGE__->__set_nillable();
__PACKAGE__->__set_minOccurs();
__PACKAGE__->__set_maxOccurs();
__PACKAGE__->__set_ref();

use base qw(
    SOAP::WSDL::XSD::Typelib::Element
    SOAP::WSDL::XSD::Typelib::ComplexType
);

our $XML_ATTRIBUTE_CLASS;
undef $XML_ATTRIBUTE_CLASS;

sub __get_attr_class {
    return $XML_ATTRIBUTE_CLASS;
}

use Class::Std::Fast::Storable constructor => 'none';
use base qw(SOAP::WSDL::XSD::Typelib::ComplexType);

Class::Std::initialize();

{ # BLOCK to scope variables

my %PTZConfiguration_of :ATTR(:get<PTZConfiguration>);

__PACKAGE__->_factory(
    [ qw(        PTZConfiguration

    ) ],
    {
        'PTZConfiguration' => \%PTZConfiguration_of,
    },
    {
        'PTZConfiguration' => 'ONVIF::PTZ::Types::PTZConfiguration',
    },
    {

        'PTZConfiguration' => 'PTZConfiguration',
    }
);

} # end BLOCK







} # end of BLOCK



1;


=pod

=head1 NAME

ONVIF::PTZ::Elements::GetConfigurationsResponse

=head1 DESCRIPTION

Perl data type class for the XML Schema defined element
GetConfigurationsResponse from the namespace http://www.onvif.org/ver20/ptz/wsdl.







=head1 PROPERTIES

The following properties may be accessed using get_PROPERTY / set_PROPERTY
methods:

=over

=item * PTZConfiguration

 $element->set_PTZConfiguration($data);
 $element->get_PTZConfiguration();





=back


=head1 METHODS

=head2 new

 my $element = ONVIF::PTZ::Elements::GetConfigurationsResponse->new($data);

Constructor. The following data structure may be passed to new():

 {
   PTZConfiguration =>  { # ONVIF::PTZ::Types::PTZConfiguration
     NodeToken => $some_value, # ReferenceToken
     DefaultAbsolutePantTiltPositionSpace =>  $some_value, # anyURI
     DefaultAbsoluteZoomPositionSpace =>  $some_value, # anyURI
     DefaultRelativePanTiltTranslationSpace =>  $some_value, # anyURI
     DefaultRelativeZoomTranslationSpace =>  $some_value, # anyURI
     DefaultContinuousPanTiltVelocitySpace =>  $some_value, # anyURI
     DefaultContinuousZoomVelocitySpace =>  $some_value, # anyURI
     DefaultPTZSpeed =>  { # ONVIF::PTZ::Types::PTZSpeed
       PanTilt => ,
       Zoom => ,
     },
     DefaultPTZTimeout =>  $some_value, # duration
     PanTiltLimits =>  { # ONVIF::PTZ::Types::PanTiltLimits
       Range =>  { # ONVIF::PTZ::Types::Space2DDescription
         URI =>  $some_value, # anyURI
         XRange =>  { # ONVIF::PTZ::Types::FloatRange
           Min =>  $some_value, # float
           Max =>  $some_value, # float
         },
         YRange =>  { # ONVIF::PTZ::Types::FloatRange
           Min =>  $some_value, # float
           Max =>  $some_value, # float
         },
       },
     },
     ZoomLimits =>  { # ONVIF::PTZ::Types::ZoomLimits
       Range =>  { # ONVIF::PTZ::Types::Space1DDescription
         URI =>  $some_value, # anyURI
         XRange =>  { # ONVIF::PTZ::Types::FloatRange
           Min =>  $some_value, # float
           Max =>  $some_value, # float
         },
       },
     },
     Extension =>  { # ONVIF::PTZ::Types::PTZConfigurationExtension
       PTControlDirection =>  { # ONVIF::PTZ::Types::PTControlDirection
         EFlip =>  { # ONVIF::PTZ::Types::EFlip
           Mode => $some_value, # EFlipMode
         },
         Reverse =>  { # ONVIF::PTZ::Types::Reverse
           Mode => $some_value, # ReverseMode
         },
         Extension =>  { # ONVIF::PTZ::Types::PTControlDirectionExtension
         },
       },
       Extension =>  { # ONVIF::PTZ::Types::PTZConfigurationExtension2
       },
     },
   },
 },

=head1 AUTHOR

Generated by SOAP::WSDL

=cut

