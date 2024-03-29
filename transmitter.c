/* Copyright (C)
* 2018 - John Melton, G0ORX/N6LYT
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*
*/

#include <gtk/gtk.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wdsp.h>
#include "alex.h"
#include "discovered.h"
#include "mode.h"
#include "filter.h"
#include "receiver.h"
#include "transmitter.h"
#include "wideband.h"
#include "adc.h"
#include "radio.h"
#include "protocol1.h"
#include "protocol2.h"
#include "tx_panadapter.h"
#include "main.h"
#include "vox.h"
#include "audio.h"
#include "mic_level.h"
#include "property.h"
#include "ext.h"

void transmitter_save_state(TRANSMITTER *tx) {
  char name[80];
  char value[80];
  int i;

  sprintf(name,"transmitter[%d].channel",tx->channel);
  sprintf(value,"%d",tx->channel);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].alex_antenna",tx->channel);
  sprintf(value,"%d",tx->alex_antenna);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].mic_gain",tx->channel);
  sprintf(value,"%f",tx->mic_gain);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].linein_gain",tx->channel);
  sprintf(value,"%d",tx->linein_gain);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].alc_meter",tx->channel);
  sprintf(value,"%d",tx->alc_meter);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].drive",tx->channel);
  sprintf(value,"%f",tx->drive);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].tune_percent",tx->channel);
  sprintf(value,"%f",tx->tune_percent);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].tune_use_drive",tx->channel);
  sprintf(value,"%d",tx->tune_use_drive);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].attenuation",tx->channel);
  sprintf(value,"%d",tx->attenuation);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].use_rx_filter",tx->channel);
  sprintf(value,"%d",tx->use_rx_filter);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].filter_low",tx->channel);
  sprintf(value,"%d",tx->filter_low);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].filter_high",tx->channel);
  sprintf(value,"%d",tx->filter_high);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].fft_size",tx->channel);
  sprintf(value,"%d",tx->fft_size);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].low_latency",tx->channel);
  sprintf(value,"%d",tx->low_latency);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].buffer_size",tx->channel);
  sprintf(value,"%d",tx->buffer_size);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].mic_samples",tx->channel);
  sprintf(value,"%d",tx->mic_samples);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].mic_sample_rate",tx->channel);
  sprintf(value,"%d",tx->mic_sample_rate);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].mic_dsp_rate",tx->channel);
  sprintf(value,"%d",tx->mic_dsp_rate);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].iq_output_rate",tx->channel);
  sprintf(value,"%d",tx->iq_output_rate);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].output_samples",tx->channel);
  sprintf(value,"%d",tx->output_samples);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].pre_emphasize",tx->channel);
  sprintf(value,"%d",tx->pre_emphasize);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].enable_equalizer",tx->channel);
  sprintf(value,"%d",tx->enable_equalizer);
  setProperty(name,value);
  for(i=0;i<4;i++) {
    sprintf(name,"transmitter[%d].eualizer[%d]",tx->channel,i);
    sprintf(value,"%d",tx->equalizer[i]);
    setProperty(name,value);
  }
  sprintf(name,"transmitter[%d].leveler",tx->channel);
  sprintf(value,"%d",tx->leveler);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].fps",tx->channel);
  sprintf(value,"%d",tx->fps);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].panadapter_low",tx->channel);
  sprintf(value,"%d",tx->panadapter_low);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].panadapter_high",tx->channel);
  sprintf(value,"%d",tx->panadapter_high);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].ctcss",tx->channel);
  sprintf(value,"%d",tx->ctcss);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].ctcss_frequency",tx->channel);
  sprintf(value,"%f",tx->ctcss_frequency);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].eer",tx->channel);
  sprintf(value,"%i",tx->eer);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].eer_amiq",tx->channel);
  sprintf(value,"%i",tx->eer_amiq);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].eer_pgain",tx->channel);
  sprintf(value,"%f",tx->eer_pgain);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].eer_mgain",tx->channel);
  sprintf(value,"%f",tx->eer_mgain);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].eer_pdelay",tx->channel);
  sprintf(value,"%f",tx->eer_pdelay);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].eer_mdelay",tx->channel);
  sprintf(value,"%f",tx->eer_mdelay);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].eer_enable_delays",tx->channel);
  sprintf(value,"%i",tx->eer_enable_delays);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].eer_pwm_min",tx->channel);
  sprintf(value,"%i",tx->eer_pwm_min);
  setProperty(name,value);
  sprintf(name,"transmitter[%d].eer_pwm_max",tx->channel);
  sprintf(value,"%i",tx->eer_pwm_max);
  setProperty(name,value);
}

void transmitter_restore_state(TRANSMITTER *tx) {
  char name[80];
  char *value;
  int i;

  sprintf(name,"transmitter[%d].channel",tx->channel);
  value=getProperty(name);
  if(value) tx->channel=atoi(value);
  sprintf(name,"transmitter[%d].alex_antenna",tx->channel);
  value=getProperty(name);
  if(value) tx->alex_antenna=atoi(value);
  sprintf(name,"transmitter[%d].mic_gain",tx->channel);
  value=getProperty(name);
  if(value) tx->mic_gain=atof(value);
  sprintf(name,"transmitter[%d].linein_gain",tx->channel);
  value=getProperty(name);
  if(value) tx->linein_gain=atoi(value);
  sprintf(name,"transmitter[%d].alc_meter",tx->channel);
  value=getProperty(name);
  if(value) tx->alc_meter=atoi(value);
  sprintf(name,"transmitter[%d].drive",tx->channel);
  value=getProperty(name);
  if(value) tx->drive=atof(value);
  sprintf(name,"transmitter[%d].tune_percent",tx->channel);
  value=getProperty(name);
  if(value) tx->tune_percent=atof(value);
  sprintf(name,"transmitter[%d].tune_use_drive",tx->channel);
  value=getProperty(name);
  if(value) tx->tune_use_drive=atoi(value);
  sprintf(name,"transmitter[%d].attenuation",tx->channel);
  value=getProperty(name);
  if(value) tx->attenuation=atoi(value);
  sprintf(name,"transmitter[%d].use_rx_filter",tx->channel);
  value=getProperty(name);
  if(value) tx->use_rx_filter=atoi(value);
  sprintf(name,"transmitter[%d].filter_low",tx->channel);
  value=getProperty(name);
  if(value) tx->filter_low=atoi(value);
  sprintf(name,"transmitter[%d].filter_high",tx->channel);
  value=getProperty(name);
  if(value) tx->filter_high=atoi(value);
  sprintf(name,"transmitter[%d].fft_size",tx->channel);
  value=getProperty(name);
  if(value) tx->fft_size=atoi(value);
  sprintf(name,"transmitter[%d].low_latency",tx->channel);
  value=getProperty(name);
  if(value) tx->low_latency=atoi(value);
  sprintf(name,"transmitter[%d].buffer_size",tx->channel);
  value=getProperty(name);
  if(value) tx->buffer_size=atoi(value);
  sprintf(name,"transmitter[%d].mic_samples",tx->channel);
  value=getProperty(name);
  if(value) tx->mic_samples=atoi(value);
  sprintf(name,"transmitter[%d].mic_sample_rate",tx->channel);
  value=getProperty(name);
  if(value) tx->mic_sample_rate=atoi(value);
  sprintf(name,"transmitter[%d].mic_dsp_rate",tx->channel);
  value=getProperty(name);
  if(value) tx->mic_dsp_rate=atoi(value);
  sprintf(name,"transmitter[%d].iq_output_rate",tx->channel);
  value=getProperty(name);
  if(value) tx->iq_output_rate=atoi(value);
  sprintf(name,"transmitter[%d].output_samples",tx->channel);
  value=getProperty(name);
  if(value) tx->output_samples=atoi(value);
  sprintf(name,"transmitter[%d].pre_emphasize",tx->channel);
  value=getProperty(name);
  if(value) tx->pre_emphasize=atoi(value);
  sprintf(name,"transmitter[%d].enable_equalizer",tx->channel);
  value=getProperty(name);
  if(value) tx->enable_equalizer=atoi(value);
  for(i=0;i<4;i++) {
    sprintf(name,"transmitter[%d].eualizer[%d]",tx->channel,i);
    value=getProperty(name);
    if(value) tx->equalizer[i]=atoi(value);
  }
  sprintf(name,"transmitter[%d].leveler",tx->channel);
  value=getProperty(name);
  if(value) tx->leveler=atoi(value);
  sprintf(name,"transmitter[%d].fps",tx->channel);
  value=getProperty(name);
  if(value) tx->fps=atoi(value);
  sprintf(name,"transmitter[%d].panadapter_low",tx->channel);
  value=getProperty(name);
  if(value) tx->panadapter_low=atoi(value);
  sprintf(name,"transmitter[%d].panadapter_high",tx->channel);
  value=getProperty(name);
  if(value) tx->panadapter_high=atoi(value);
  sprintf(name,"transmitter[%d].ctcss",tx->channel);
  value=getProperty(name);
  if(value) tx->ctcss=atoi(value);
  sprintf(name,"transmitter[%d].ctcss_frequency",tx->channel);
  value=getProperty(name);
  if(value) tx->ctcss_frequency=atof(value);
  sprintf(name,"transmitter[%d].eer",tx->channel);
  value=getProperty(name);
  if(value) tx->eer=atoi(value);
  sprintf(name,"transmitter[%d].eer_amiq",tx->channel);
  value=getProperty(name);
  if(value) tx->eer_amiq=atoi(value);
  sprintf(name,"transmitter[%d].eer_pgain",tx->channel);
  value=getProperty(name);
  if(value) tx->eer_pgain=atof(value);
  sprintf(name,"transmitter[%d].eer_mgain",tx->channel);
  value=getProperty(name);
  if(value) tx->eer_mgain=atof(value);
  sprintf(name,"transmitter[%d].eer_pdelay",tx->channel);
  value=getProperty(name);
  if(value) tx->eer_pdelay=atof(value);
  sprintf(name,"transmitter[%d].eer_mdelay",tx->channel);
  value=getProperty(name);
  if(value) tx->eer_mdelay=atof(value);
  sprintf(name,"transmitter[%d].eer_enable_delays",tx->channel);
  value=getProperty(name);
  if(value) tx->eer_enable_delays=atoi(value);
  sprintf(name,"transmitter[%d].eer_pwm_min",tx->channel);
  value=getProperty(name);
  if(value) tx->eer_pwm_min=atoi(value);
  sprintf(name,"transmitter[%d].eer_pwm_max",tx->channel);
  value=getProperty(name);
  if(value) tx->eer_pwm_max=atoi(value);
}

static gboolean update_timer_cb(void *data) {
  int rc;
  double constant1;
  double constant2;

  TRANSMITTER *tx=(TRANSMITTER *)data;
  //if(isTransmitting(radio)) {
    GetPixels(tx->channel,0,tx->pixel_samples,&rc);
    if(rc) {
      update_tx_panadapter(radio);
    }
  //}

  update_mic_level(radio);

  if(isTransmitting(radio)) {
    tx->alc=GetTXAMeter(tx->channel,tx->alc_meter);

    switch(radio->discovered->device) {
      case DEVICE_METIS:
        constant1=3.3;
        constant2=0.09;
        break;
      case DEVICE_HERMES:
        constant1=3.3;
        constant2=0.095;
        break;
      case DEVICE_HERMES2:
        constant1=3.3;
        constant2=0.095;
        break;
      case DEVICE_ANGELIA:
        constant1=3.3;
        constant2=0.095;
        break;
      case DEVICE_ORION:
        constant1=5.0;
        constant2=0.108;
        break;
      case DEVICE_ORION2:
        constant1=5.0;
        constant2=0.108;
        break;
      case DEVICE_HERMES_LITE:
        constant1=3.3;
        constant2=0.095;
        break;
    }

    int power=tx->alex_forward_power;
    if(power==0) {
      power=tx->exciter_power;
    }
    double v1;
    v1=((double)power/4095.0)*constant1;
    tx->fwd=(v1*v1)/constant2;

    power=tx->exciter_power;
    v1=((double)power/4095.0)*constant1;
    tx->exciter=(v1*v1)/constant2;

    tx->rev=0.0;
    if(tx->alex_forward_power!=0) {
      power=tx->alex_reverse_power;
      v1=((double)power/4095.0)*constant1;
      tx->rev=(v1*v1)/constant2;
    }
    
  }

  return TRUE;
}

void transmitter_fps_changed(TRANSMITTER *tx) {
  g_source_remove(tx->update_timer_id);
  tx->update_timer_id=g_timeout_add(1000/tx->fps,update_timer_cb,(gpointer)tx);
}

void transmitter_set_ps(TRANSMITTER *tx,gboolean state) {
  tx->puresignal=state;
  if(state) {
    SetPSControl(tx->channel, 0, 0, 1, 0);
  } else {
    SetPSControl(tx->channel, 1, 0, 0, 0);
  }
}

void transmitter_enable_eer(TRANSMITTER *tx,gboolean state) {
  tx->eer=state;
  SetEERRun(0, tx->eer);
}
void transmitter_set_eer_mode_amiq(TRANSMITTER *tx,gboolean state) {
  tx->eer_amiq=state;
  SetEERAMIQ(0, tx->eer_amiq); // 0=phase only, 1=magnitude and phase, 2=magnitude only (not supported here)
}

void transmitter_enable_eer_delays(TRANSMITTER *tx,gboolean state) {
  tx->eer_enable_delays=state;
  SetEERRunDelays(0, tx->eer_enable_delays);
}

void transmitter_set_eer_pgain(TRANSMITTER *tx,gdouble gain) {
  tx->eer_pgain=gain;
  SetEERPgain(0, tx->eer_pgain);
}

void transmitter_set_eer_pdelay(TRANSMITTER *tx,gdouble delay) {
  tx->eer_pdelay=delay;
  SetEERPdelay(0, tx->eer_pdelay/1e6);
}

void transmitter_set_eer_mgain(TRANSMITTER *tx,gdouble gain) {
  tx->eer_mgain=gain;
  SetEERMgain(0, tx->eer_mgain);
}

void transmitter_set_eer_mdelay(TRANSMITTER *tx,gdouble delay) {
  tx->eer_mdelay=delay;
  SetEERMdelay(0, tx->eer_mdelay/1e6);
}

void transmitter_set_twotone(TRANSMITTER *tx,gboolean state) {
g_print("transmitter_set_twotone: %d\n",state);
  tx->ps_twotone=state;
  if(state) {
    SetTXAPostGenMode(tx->channel, 1);
    SetTXAPostGenRun(tx->channel, 1);
  } else {
    SetTXAPostGenRun(tx->channel, 0);
  }
/*
  MOX *m=g_new0(MOX,1);
  m->radio=radio;
  m->state=state;
  g_idle_add(ext_set_mox,(gpointer)m);
*/
  set_mox(radio,state);
}

void transmitter_set_ps_sample_rate(TRANSMITTER *tx,int rate) {
  SetPSFeedbackRate (tx->channel,rate);
}

static void full_tx_buffer(TRANSMITTER *tx) {
  long isample;
  long qsample;
  long lsample;
  long rsample;
  double gain;
  int j;
  int error;
  int mode;

// round half towards zero
#define ROUNDHTZ(x) ((x)>=0.0?(long)floor((x)*gain+0.5):(long)ceil((x)*gain-0.5))

  switch(radio->discovered->protocol) {
#ifdef RADIOBERRY
    case RADIOBERRY_PROTOCOL:
#endif
    case PROTOCOL_1:
      gain=32767.0;  // 16 bit
      break;
    case PROTOCOL_2:
      gain=8388607.0; // 24 bit
      break;
  }

  update_vox(radio);

  fexchange0(tx->channel, tx->mic_input_buffer, tx->iq_output_buffer, &error);
  if(error!=0) {
//    fprintf(stderr,"full_tx_buffer: channel=%d fexchange0: error=%d\n",tx->channel,error);
  }

  Spectrum0(1, tx->channel, 0, 0, tx->iq_output_buffer);

  if(isTransmitting(radio)) {
/*
    if(radio->discovered->device==NEW_DEVICE_ATLAS && atlas_penelope) {
      if(radio->tune && !transmitter->tune_use_drive) {
        gain=gain*(transmitter->drive*100.0/(double)transmitter->tune_percent);
      } else {
        gain=gain*transmitter->drive;
      }
    }
*/

    for(j=0;j<tx->output_samples;j++) {
      tx->inI[j]=tx->iq_output_buffer[j*2];
      tx->inQ[j]=tx->iq_output_buffer[(j*2)+1];
    }
    // EER processing
    // input is TX IQ samples in inI,inQ
    // output phase/IQ/magnitude is written back to inI,inQ and
    //   outMI,outMQ contain the scaled and delayed input samples
    xeerEXTF(0, tx->inI, tx->inQ, tx->inI, tx->inQ, tx->outMI, tx->outMQ, isTransmitting(radio), tx->output_samples);

    for(j=0;j<tx->output_samples;j++) {
      isample=ROUNDHTZ(tx->inI[j]);
      qsample=ROUNDHTZ(tx->inQ[j]);
      lsample=ROUNDHTZ(tx->outMI[j]);
      rsample=ROUNDHTZ(tx->outMQ[j]);
      switch(radio->discovered->protocol) {
        case PROTOCOL_1:
          protocol1_iq_samples(isample,qsample,lsample,rsample);
          break;
        case PROTOCOL_2:
          protocol2_iq_samples(isample,qsample);
          break;
/*
#ifdef RADIOBERRY
        case RADIOBERRY_PROTOCOL:
          radioberry_protocol_iq_samples(isample,qsample);
          break;
#endif
*/
      }
    }
  }
#undef ROUNDHTZ
}

void add_mic_sample(TRANSMITTER *tx,short mic_sample) {
  int mode;
  double sample;
  double mic_sample_double;
  int i,s;
 
  if(tx->rx!=NULL) {
    mode=tx->rx->mode_a;

    if(mode==CWL || mode==CWU || radio->tune) {
      mic_sample_double=0.0;
    } else {
      mic_sample_double=(double)mic_sample/32768.0;
    }
    tx->mic_input_buffer[tx->mic_samples*2]=mic_sample_double;
    tx->mic_input_buffer[(tx->mic_samples*2)+1]=0.0; //mic_sample_double;
    tx->mic_samples++;
    if(tx->mic_samples==tx->buffer_size) {
      full_tx_buffer(tx);
      tx->mic_samples=0;
    }
#ifdef AUDIO_WATERFALL
    if(audio_samples!=NULL && isTransmitting(radio)) {
      if(waterfall_samples==0) {
         audio_samples[audio_samples_index]=(float)mic_sample;
         audio_samples_index++;
         if(audio_samples_index>=AUDIO_WATERFALL_SAMPLES) {
           //Spectrum(CHANNEL_AUDIO,0,0,audio_samples,audio_samples);
           audio_samples_index=0;
       }
       }
       waterfall_samples++;
       if(waterfall_samples==waterfall_resample) {
         waterfall_samples=0;
       }
    }
#endif
  }
}

void transmitter_set_filter(TRANSMITTER *tx,int low,int high) {

  gint mode=USB;
  if(tx->rx!=NULL) {
    if(tx->rx->split) {
      mode=tx->rx->mode_b;
    } else {
      mode=tx->rx->mode_a;
    } 
  }
  if(tx->use_rx_filter) {
    RECEIVER *rx=tx->rx;
    FILTER *mode_filters=filters[mode];
    FILTER *filter=&mode_filters[F5];
    if(rx!=NULL) {
      if(rx->split) {
        filter=&mode_filters[rx->filter_b];
      } else {
        filter=&mode_filters[rx->filter_a];
      }
    }
    if(mode==CWL) {
      tx->actual_filter_low=-radio->cw_keyer_sidetone_frequency-filter->low;
      tx->actual_filter_high=-radio->cw_keyer_sidetone_frequency+filter->high;
    } else if(mode==CWU) {
      tx->actual_filter_low=radio->cw_keyer_sidetone_frequency-filter->low;
      tx->actual_filter_high=radio->cw_keyer_sidetone_frequency+filter->high;
    } else {
      tx->actual_filter_low=filter->low;
      tx->actual_filter_high=filter->high;
    }
  } else {
    switch(mode) {
      case LSB:
      case CWL:
      case DIGL:
        tx->actual_filter_low=-high;
        tx->actual_filter_high=-low;
        break;
      case USB:
      case CWU:
      case DIGU:
        tx->actual_filter_low=low;
        tx->actual_filter_high=high;
        break;
      case DSB:
      case AM:
      case SAM:
        tx->actual_filter_low=-high;
        tx->actual_filter_high=high;
        break;
      case FMN:
        if(tx->deviation==2500) {
          tx->actual_filter_low=-4000;
          tx->actual_filter_high=4000;
        } else {
          tx->actual_filter_low=-8000;
          tx->actual_filter_high=8000;
        }
        break;
      case DRM:
        tx->actual_filter_low=7000;
        tx->actual_filter_high=17000;
        break;
    }
  }
  double fl=tx->actual_filter_low;
  double fh=tx->actual_filter_high;

  SetTXABandpassFreqs(tx->channel, fl,fh);

  if(tx->panadapter != NULL) {
    update_tx_panadapter(radio);
  }
}


void transmitter_set_mode(TRANSMITTER* tx,int mode) {
  if(tx!=NULL) {
    SetTXAMode(tx->channel, mode);
    transmitter_set_filter(tx,tx->filter_low,tx->filter_high);
  }
}

void transmitter_set_deviation(TRANSMITTER *tx) {
  SetTXAFMDeviation(tx->channel, (double)tx->deviation);
}

void transmitter_set_am_carrier_level(TRANSMITTER *tx) {
  SetTXAAMCarrierLevel(tx->channel, tx->am_carrier_level);
}

void transmitter_set_ctcss(TRANSMITTER *tx,gboolean run,gdouble frequency) {
  tx->ctcss=run;
  tx->ctcss_frequency=frequency;
  SetTXACTCSSFreq(tx->channel, tx->ctcss_frequency);
  SetTXACTCSSRun(tx->channel, tx->ctcss);
}

void transmitter_set_pre_emphasize(TRANSMITTER *tx,int state) {
  SetTXAFMEmphPosition(tx->channel,state);
}

static gboolean transmitter_configure_event_cb(GtkWidget *widget,GdkEventConfigure *event,gpointer data) {
  TRANSMITTER *tx=(TRANSMITTER *)data;
  tx->window_width=gtk_widget_get_allocated_width(widget);
  tx->window_height=gtk_widget_get_allocated_height(widget);
  g_print("transmitter_configure_event_cb: wid=%d height=%d\n",tx->window_width,tx->window_height);
  return TRUE;
}

static void create_visual(TRANSMITTER *tx) {
  gchar title[32];
  g_snprintf((gchar *)&title,sizeof(title),"LinHPSDR: Rx:%d",tx->channel);

/*
  tx->window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(tx->window),title);
  gtk_widget_set_size_request(tx->window,tx->window_width,tx->window_height);

  rx->table=gtk_table_new(3,4,FALSE);

  rx->vfo=create_vfo(rx);
  gtk_widget_set_size_request(rx->vfo,600,60);
  gtk_table_attach(GTK_TABLE(rx->table), rx->vfo, 0, 3, 0, 1,
      GTK_FILL, GTK_FILL, 0, 0);

  rx->meter=create_meter_visual(rx);
  gtk_widget_set_size_request(rx->meter,200,60);
  gtk_table_attach(GTK_TABLE(rx->table), rx->meter, 2, 4, 0, 1,
      GTK_FILL, GTK_FILL, 0, 0);

  rx->panadapter=create_rx_panadapter(rx);
  gtk_table_attach(GTK_TABLE(rx->table), rx->panadapter, 0, 4, 1, 2,
      GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

  rx->waterfall=create_waterfall(rx);
  gtk_table_attach(GTK_TABLE(rx->table), rx->waterfall, 0, 4, 2, 3,
      GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

  gtk_container_add(GTK_CONTAINER(rx->window),rx->table);
*/
  tx->panadapter=create_tx_panadapter(tx);
  //tx->mic_level=create_mic_level(tx);

//  gtk_container_add(GTK_CONTAINER(tx->window),tx->panadapter);

}

void transmitter_init_analyzer(TRANSMITTER *tx) {
    int flp[] = {0};
    double keep_time = 0.1;
    int n_pixout=1;
    int spur_elimination_ffts = 1;
    int data_type = 1;
    int fft_size = 8192;
    int window_type = 4;
    double kaiser_pi = 14.0;
    int overlap = 2048;
    int clip = 0;
    int span_clip_l = 0;
    int span_clip_h = 0;
    int pixels=tx->pixels;
    int stitches = 1;
    int avm = 0;
    double tau = 0.001 * 120.0;
    int calibration_data_set = 0;
    double span_min_freq = 0.0;
    double span_max_freq = 0.0;

    g_print("transmitter_init_analyzer: width=%d pixels=%d\n",tx->panadapter_width,tx->pixels);

    if(tx->pixel_samples!=NULL) {
      g_free(tx->pixel_samples);
      tx->pixel_samples=NULL;
    }

    if(tx->pixels>0) {
      tx->pixel_samples=g_new0(float,tx->pixels);
      int max_w = fft_size + (int) min(keep_time * (double) tx->fps, keep_time * (double) fft_size * (double) tx->fps);

      overlap = (int)max(0.0, ceil(fft_size - (double)tx->mic_sample_rate / (double)tx->fps));

      fprintf(stderr,"SetAnalyzer id=%d buffer_size=%d overlap=%d\n",tx->channel,tx->output_samples,overlap);


      SetAnalyzer(tx->channel,
            n_pixout,
            spur_elimination_ffts, //number of LO frequencies = number of ffts used in elimination
            data_type, //0 for real input data (I only); 1 for complex input data (I & Q)
            flp, //vector with one elt for each LO frequency, 1 if high-side LO, 0 otherwise
            fft_size, //size of the fft, i.e., number of input samples
            tx->output_samples, //number of samples transferred for each OpenBuffer()/CloseBuffer()
            window_type, //integer specifying which window function to use
            kaiser_pi, //PiAlpha parameter for Kaiser window
            overlap, //number of samples each fft (other than the first) is to re-use from the previous
            clip, //number of fft output bins to be clipped from EACH side of each sub-span
            span_clip_l, //number of bins to clip from low end of entire span
            span_clip_h, //number of bins to clip from high end of entire span
            pixels, //number of pixel values to return.  may be either <= or > number of bins
            stitches, //number of sub-spans to concatenate to form a complete span
            calibration_data_set, //identifier of which set of calibration data to use
            span_min_freq, //frequency at first pixel value8192
            span_max_freq, //frequency at last pixel value
            max_w //max samples to hold in input ring buffers
      );
  }

}


TRANSMITTER *create_transmitter(int channel) {
  gint rc;
g_print("create_transmitter: channel=%d\n",channel);
  TRANSMITTER *tx=g_new0(TRANSMITTER,1);
  tx->channel=channel;
  tx->alex_antenna=ALEX_TX_ANTENNA_1;
  tx->mic_gain=0.0;
  tx->rx=NULL;

  tx->alc_meter=TXA_ALC_PK;
  tx->exciter_power=0;
  tx->alex_forward_power=0;
  tx->alex_reverse_power=0;

  tx->eer_amiq=1;
  tx->eer_pgain=0.5;
  tx->eer_mgain=0.5;
  tx->eer_pdelay=200;
  tx->eer_mdelay=200;
  tx->eer_enable_delays=TRUE;
  tx->eer_pwm_min=100;
  tx->eer_pwm_max=800;

  tx->use_rx_filter=FALSE;
  tx->filter_low=150;
  tx->filter_high=2850;

  tx->actual_filter_low=tx->filter_low;
  tx->actual_filter_high=tx->filter_high;

  tx->fft_size=2048;
  tx->low_latency=FALSE;

  if(radio->discovered->protocol==PROTOCOL_1) {
    tx->mic_sample_rate=48000;
    tx->mic_dsp_rate=48000;
    tx->iq_output_rate=48000;
    tx->buffer_size=1024;
    tx->output_samples=1024;
  } else {
    tx->mic_sample_rate=48000;
    tx->mic_dsp_rate=96000;
    tx->iq_output_rate=192000;
    tx->buffer_size=1024;
    tx->output_samples=4096;
  }

  tx->mic_samples=0;
  tx->mic_input_buffer=g_new(gdouble,2*tx->buffer_size);
  tx->iq_output_buffer=g_new(gdouble,2*tx->output_samples);

  // EER buffers
  tx->inI=g_new(gfloat,tx->output_samples);
  tx->inQ=g_new(gfloat,tx->output_samples);
  tx->outMI=g_new(gfloat,tx->output_samples);
  tx->outMQ=g_new(gfloat,tx->output_samples);

  tx->pre_emphasize=FALSE;
  tx->enable_equalizer=FALSE;
  tx->equalizer[0]=tx->equalizer[1]=tx->equalizer[2]=tx->equalizer[3]=0;
  tx->leveler=FALSE;

  tx->ctcss=FALSE;
  tx->ctcss_frequency=100.0;
  tx->tone_level=0.2;

  tx->deviation=2500.0;

  tx->compressor=FALSE;
  tx->compressor_level=0.0;

  tx->am_carrier_level=0.5;

  tx->fps=10;
  tx->pixels=0;
  tx->pixel_samples=NULL;

  tx->drive=20.0;
  tx->tune_use_drive=FALSE;
  tx->tune_percent=10.0;

  tx->panadapter_high=20;
  tx->panadapter_low=-140;
  tx->panadapter=NULL;
  tx->panadapter_surface=NULL;

  tx->puresignal=FALSE;
  tx->ps_twotone=FALSE;
  tx->ps_feedback=FALSE;
  tx->ps_auto=TRUE;
  tx->ps_single=FALSE;

  tx->dialog=NULL;

  gint mode=USB;

  transmitter_restore_state(tx);

  OpenChannel(tx->channel,
              tx->buffer_size,
              2048, // tx->fft_size,
              tx->mic_sample_rate,
              tx->mic_dsp_rate,
              tx->iq_output_rate,
              1, // transmit
              0, // run
              0.010, 0.025, 0.0, 0.010, 0);

  TXASetNC(tx->channel, tx->fft_size);
  TXASetMP(tx->channel, tx->low_latency);

  SetTXABandpassWindow(tx->channel, 1);
  SetTXABandpassRun(tx->channel, 1);

  SetTXAFMEmphPosition(tx->channel,tx->pre_emphasize);

  SetTXACFIRRun(tx->channel, 0);
  SetTXAGrphEQ(tx->channel, tx->equalizer);
  if(tx->enable_equalizer) {
    SetTXAEQRun(tx->channel, 1);
  } else {
    SetTXAEQRun(tx->channel, 0);
  }

  transmitter_set_ctcss(tx,tx->ctcss,tx->ctcss_frequency);
  SetTXAAMSQRun(tx->channel, 0);
  SetTXAosctrlRun(tx->channel, 0);

  SetTXAALCAttack(tx->channel, 1);
  SetTXAALCDecay(tx->channel, 10);
  SetTXAALCSt(tx->channel, 1); // turn it on (always on)

  SetTXALevelerAttack(tx->channel, 1);
  SetTXALevelerDecay(tx->channel, 500);
  SetTXALevelerTop(tx->channel, 5.0);
  SetTXALevelerSt(tx->channel, tx->leveler);

  SetTXAPreGenMode(tx->channel, 0);
  SetTXAPreGenToneMag(tx->channel, 0.0);
  SetTXAPreGenToneFreq(tx->channel, 0.0);
  SetTXAPreGenRun(tx->channel, 0);

  SetTXAPostGenMode(tx->channel, 0);
  SetTXAPostGenToneMag(tx->channel, tx->tone_level);
  SetTXAPostGenTTMag(tx->channel, tx->tone_level,tx->tone_level);
  SetTXAPostGenToneFreq(tx->channel, 0.0);
  SetTXAPostGenRun(tx->channel, 0);

  SetTXAPanelGain1(tx->channel,pow(10.0, tx->mic_gain / 20.0));
  SetTXAPanelRun(tx->channel, 1);

  SetTXAFMDeviation(tx->channel, tx->deviation);
  SetTXAAMCarrierLevel(tx->channel, tx->am_carrier_level);

  SetTXACompressorGain(tx->channel, tx->compressor_level);
  SetTXACompressorRun(tx->channel, tx->compressor);

  create_eerEXT(0, // id
                0, // run
                tx->buffer_size, // size
                48000, // rate
                tx->eer_mgain, // mgain
                tx->eer_pgain, // pgain
                tx->eer_enable_delays, // rundelays
                tx->eer_mdelay/1e6, // mdelay
                tx->eer_pdelay/1e6, // pdelay
                tx->eer_amiq); // amiq

  SetEERRun(0, 1);

  transmitter_set_mode(tx,mode);

  create_visual(tx);

  XCreateAnalyzer(tx->channel, &rc, 262144, 1, 1, "");
  if (rc != 0) {
    fprintf(stderr, "XCreateAnalyzer channel=%d failed: %d\n",tx->channel,rc);
  } else {
    transmitter_init_analyzer(tx);
g_print("update_timer: fps=%d\n",tx->fps);
    tx->update_timer_id=g_timeout_add(1000/tx->fps,update_timer_cb,(gpointer)tx);
  }
  return tx;
}
