package ONVIF::Media::Types::AudioDecoderConfigurationOptions;
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

my %AACDecOptions_of :ATTR(:get<AACDecOptions>);
my %G711DecOptions_of :ATTR(:get<G711DecOptions>);
my %G726DecOptions_of :ATTR(:get<G726DecOptions>);
my %Extension_of :ATTR(:get<Extension>);

__PACKAGE__->_factory(
    [ qw(        AACDecOptions
        G711DecOptions
        G726DecOptions
        Extension

    ) ],
    {
        'AACDecOptions' => \%AACDecOptions_of,
        'G711DecOptions' => \%G711DecOptions_of,
        'G726DecOptions' => \%G726DecOptions_of,
        'Extension' => \%Extension_of,
    },
    {
        'AACDecOptions' => 'ONVIF::Media::Types::AACDecOptions',
        'G711DecOptions' => 'ONVIF::Media::Types::G711DecOptions',
        'G726DecOptions' => 'ONVIF::Media::Types::G726DecOptions',
        'Extension' => 'ONVIF::Media::Types::AudioDecoderConfigurationOptionsExtension',
    },
    {

        'AACDecOptions' => 'AACDecOptions',
        'G711DecOptions' => 'G711DecOptions',
        'G726DecOptions' => 'G726DecOptions',
        'Extension' => 'Extension',
    }
);

} # end BLOCK








1;


=pod

=head1 NAME

ONVIF::Media::Types::AudioDecoderConfigurationOptions

=head1 DESCRIPTION

Perl data type class for the XML Schema defined complexType
AudioDecoderConfigurationOptions from the namespace http://www.onvif.org/ver10/schema.






=head2 PROPERTIES

The following properties may be accessed using get_PROPERTY / set_PROPERTY
methods:

=over

=item * AACDecOptions


=item * G711DecOptions


=item * G726DecOptions


=item * Extension




=back


=head1 METHODS

=head2 new

Constructor. The following data structure may be passed to new():

 { # ONVIF::Media::Types::AudioDecoderConfigurationOptions
   AACDecOptions =>  { # ONVIF::Media::Types::AACDecOptions
     Bitrate =>  { # ONVIF::Media::Types::IntList
       Items =>  $some_value, # int
     },
     SampleRateRange =>  { # ONVIF::Media::Types::IntList
       Items =>  $some_value, # int
     },
   },
   G711DecOptions =>  { # ONVIF::Media::Types::G711DecOptions
     Bitrate =>  { # ONVIF::Media::Types::IntList
       Items =>  $some_value, # int
     },
     SampleRateRange =>  { # ONVIF::Media::Types::IntList
       Items =>  $some_value, # int
     },
   },
   G726DecOptions =>  { # ONVIF::Media::Types::G726DecOptions
     Bitrate =>  { # ONVIF::Media::Types::IntList
       Items =>  $some_value, # int
     },
     SampleRateRange =>  { # ONVIF::Media::Types::IntList
       Items =>  $some_value, # int
     },
   },
   Extension =>  { # ONVIF::Media::Types::AudioDecoderConfigurationOptionsExtension
   },
 },




=head1 AUTHOR

Generated by SOAP::WSDL

=cut

