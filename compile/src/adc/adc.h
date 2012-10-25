#ifndef _ADC_H
#define _ADC_H

#ifdef ADC_DYNCHANNELS
#define ADC_NBCHANNELS 8
extern volatile unsigned char adcNbChannels;
#define ADC_ROTATECHANNELS adcNbChannels
#else
#define ADC_ROTATECHANNELS ADC_NBCHANNELS
#endif

#ifndef ADC_NBCHANNELS
#define ADC_NBCHANNELS 1
#endif

extern volatile unsigned int adcValues[ADC_NBCHANNELS];

void adc_run(int free);

#endif
