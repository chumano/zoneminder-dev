package ONVIF::Device::Types::ExposureOptions;
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
my %Priority_of :ATTR(:get<Priority>);
my %MinExposureTime_of :ATTR(:get<MinExposureTime>);
my %MaxExposureTime_of :ATTR(:get<MaxExposureTime>);
my %MinGain_of :ATTR(:get<MinGain>);
my %MaxGain_of :ATTR(:get<MaxGain>);
my %MinIris_of :ATTR(:get<MinIris>);
my %MaxIris_of :ATTR(:get<MaxIris>);
my %ExposureTime_of :ATTR(:get<ExposureTime>);
my %Gain_of :ATTR(:get<Gain>);
my %Iris_of :ATTR(:get<Iris>);

__PACKAGE__->_factory(
    [ qw(        Mode
        Priority
        MinExposureTime
        MaxExposureTime
        MinGain
        MaxGain
        MinIris
        MaxIris
        ExposureTime
        Gain
        Iris

    ) ],
    {
        'Mode' => \%Mode_of,
        'Priority' => \%Priority_of,
        'MinExposureTime' => \%MinExposureTime_of,
        'MaxExposureTime' => \%MaxExposureTime_of,
        'MinGain' => \%MinGain_of,
        'MaxGain' => \%MaxGain_of,
        'MinIris' => \%MinIris_of,
        'MaxIris' => \%MaxIris_of,
        'ExposureTime' => \%ExposureTime_of,
        'Gain' => \%Gain_of,
        'Iris' => \%Iris_of,
    },
    {
        'Mode' => 'ONVIF::Device::Types::ExposureMode',
        'Priority' => 'ONVIF::Device::Types::ExposurePriority',
        'MinExposureTime' => 'ONVIF::Device::Types::FloatRange',
        'MaxExposureTime' => 'ONVIF::Device::Types::FloatRange',
        'MinGain' => 'ONVIF::Device::Types::FloatRange',
        'MaxGain' => 'ONVIF::Device::Types::FloatRange',
        'MinIris' => 'ONVIF::Device::Types::FloatRange',
        'MaxIris' => 'ONVIF::Device::Types::FloatRange',
        'ExposureTime' => 'ONVIF::Device::Types::FloatRange',
        'Gain' => 'ONVIF::Device::Types::FloatRange',
        'Iris' => 'ONVIF::Device::Types::FloatRange',
    },
    {

        'Mode' => 'Mode',
        'Priority' => 'Priority',
        'MinExposureTime' => 'MinExposureTime',
        'MaxExposureTime' => 'MaxExposureTime',
        'MinGain' => 'MinGain',
        'MaxGain' => 'MaxGain',
        'MinIris' => 'MinIris',
        'MaxIris' => 'MaxIris',
        'ExposureTime' => 'ExposureTime',
        'Gain' => 'Gain',
        'Iris' => 'Iris',
    }
);

} # end BLOCK








1;


=pod

=head1 NAME

ONVIF::Device::Types::ExposureOptions

=head1 DESCRIPTION

Perl data type class for the XML Schema defined complexType
ExposureOptions from the namespace http://www.onvif.org/ver10/schema.






=head2 PROPERTIES

The following properties may be accessed using get_PROPERTY / set_PROPERTY
methods:

=over

=item * Mode


=item * Priority


=item * MinExposureTime


=item * MaxExposureTime


=item * MinGain


=item * MaxGain


=item * MinIris


=item * MaxIris


=item * ExposureTime


=item * Gain


=item * Iris




=back


=head1 METHODS

=head2 new

Constructor. The following data structure may be passed to new():

 { # ONVIF::Device::Types::ExposureOptions
   Mode => $some_value, # ExposureMode
   Priority => $some_value, # ExposurePriority
   MinExposureTime =>  { # ONVIF::Device::Types::FloatRange
     Min =>  $some_value, # float
     Max =>  $some_value, # float
   },
   MaxExposureTime =>  { # ONVIF::Device::Types::FloatRange
     Min =>  $some_value, # float
     Max =>  $some_value, # float
   },
   MinGain =>  { # ONVIF::Device::Types::FloatRange
     Min =>  $some_value, # float
     Max =>  $some_value, # float
   },
   MaxGain =>  { # ONVIF::Device::Types::FloatRange
     Min =>  $some_value, # float
     Max =>  $some_value, # float
   },
   MinIris =>  { # ONVIF::Device::Types::FloatRange
     Min =>  $some_value, # float
     Max =>  $some_value, # float
   },
   MaxIris =>  { # ONVIF::Device::Types::FloatRange
     Min =>  $some_value, # float
     Max =>  $some_value, # float
   },
   ExposureTime =>  { # ONVIF::Device::Types::FloatRange
     Min =>  $some_value, # float
     Max =>  $some_value, # float
   },
   Gain =>  { # ONVIF::Device::Types::FloatRange
     Min =>  $some_value, # float
     Max =>  $some_value, # float
   },
   Iris =>  { # ONVIF::Device::Types::FloatRange
     Min =>  $some_value, # float
     Max =>  $some_value, # float
   },
 },




=head1 AUTHOR

Generated by SOAP::WSDL

=cut

