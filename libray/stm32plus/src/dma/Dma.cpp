/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "config/stdperiph.h"
#include "dma/Dma.h"
#include "error/ErrorProvider.h"
#include "config/interrupts.h"

namespace stm32plus {

    /**
     * Since only one DMA channel handler can exist at any one time, the class constructor will place a
     * pointer to itself in one of these array slots. This allows the interrupt handler to get a reference
     * to the class that caused the interrupt.
     */

    Dma *Dma::Dma1_ChannelHandlers[7];
    Dma *Dma::Dma2_ChannelHandlers[5];

    /**
     * Constructor.
     * @param[in] channel The DMA channel that we are using.
     * @param[in] interruptFlags If there is an observer then these are the interrupts that we are observing.
     */

    Dma::Dma(DMA_Channel_TypeDef *channel,uint32_t interruptFlags) {

        // default values

        DMA_StructInit(this);

        // save channel and get peripheral index

        _channel=channel;
        _interruptFlags=interruptFlags;

        setPeripheral();

        // initialise the clock

        if(_dmaPeripheral == 1) {
            RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
            Dma1_ChannelHandlers[_channelIndex - 1]=this;
        } else {
            RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2,ENABLE);
            Dma2_ChannelHandlers[_channelIndex - 1]=this;
        }

        // if there are interrupts, enable them in the nvic

        if(interruptFlags!=0) {
            Nvic::configureIrq(_nvic);
            enableInterrupts(interruptFlags);
        }
    }

    /**
     * Destructor. De-initialises the channel.
     */

    Dma::~Dma() {
        DMA_Cmd(_channel,DISABLE);
        DMA_DeInit(_channel);
    }

    /**
     * Start a DMA transfer. De-inits the current channel, inits it and issues
     * an ENABLE command.
     */

    void Dma::start() {
        DMA_Cmd(_channel,DISABLE);
        DMA_DeInit(_channel);

        DMA_Init(_channel,this);

        if(_interruptFlags!=0)
            DMA_ITConfig(_channel,_interruptFlags,ENABLE);

        DMA_Cmd(_channel,ENABLE);
    }

    /**
     * Enable DMA interrupts for this channel. The flags say which ones you want to enable.
     * @param[in] interruptFlags_
     *   A combination of DMA_IT_TC (transfer complete), DMA_IT_HT (half-transfer complete), DMA_IT_TE (transfer error)
     */

    void Dma::enableInterrupts(uint32_t interruptFlags_) {
        DMA_ITConfig(_channel,interruptFlags_,ENABLE);
    }

    /*
     * Set the peripheral index from the channel typedef
     */

    void Dma::setPeripheral() {

        if(_channel == DMA1_Channel1) {
            _dmaPeripheral=1;
            _channelIndex=1;
            _nvic=DMA1_Channel1_IRQn;
        } else if(_channel == DMA1_Channel2) {
            _dmaPeripheral=1;
            _channelIndex=2;
            _nvic=DMA1_Channel2_IRQn;
        } else if(_channel == DMA1_Channel3) {
            _dmaPeripheral=1;
            _channelIndex=3;
            _nvic=DMA1_Channel3_IRQn;
        } else if(_channel == DMA1_Channel4) {
            _dmaPeripheral=1;
            _channelIndex=4;
            _nvic=DMA1_Channel4_IRQn;
        } else if(_channel == DMA1_Channel5) {
            _dmaPeripheral=1;
            _channelIndex=5;
            _nvic=DMA1_Channel5_IRQn;
        } else if(_channel == DMA1_Channel6) {
            _dmaPeripheral=1;
            _channelIndex=6;
            _nvic=DMA1_Channel6_IRQn;
        } else if(_channel == DMA1_Channel7) {
            _dmaPeripheral=1;
            _channelIndex=7;
            _nvic=DMA1_Channel7_IRQn;
        } else if(_channel == DMA2_Channel1) {
            _dmaPeripheral=2;
            _channelIndex=1;
            _nvic=DMA2_Channel1_IRQn;
        } else if(_channel == DMA2_Channel2) {
            _dmaPeripheral=2;
            _channelIndex=2;
            _nvic=DMA2_Channel2_IRQn;
        } else if(_channel == DMA2_Channel3) {
            _dmaPeripheral=2;
            _channelIndex=3;
            _nvic=DMA2_Channel3_IRQn;
        } else if(_channel == DMA2_Channel4) {
            _dmaPeripheral=2;
            _channelIndex=4;
            _nvic=DMA2_Channel4_5_IRQn;
        } else if(_channel == DMA2_Channel5) {
            _dmaPeripheral=2;
            _channelIndex=5;
            _nvic=DMA2_Channel4_5_IRQn;
        }
    }

    /**
     * Block the CPU and Wait until the DMA transfer is complete. There must be a DMA transfer
     * started on this channel or this function will hang forever.
     *
     * @return true if the transfer completes OK, false if there is a DMA error while waiting
     */

    bool Dma::waitUntilComplete() const {

        uint32_t completeFlag,errorFlag;

        completeFlag=getTransferCompleteFlag();
        errorFlag=getTransferErrorFlag();

        while(!DMA_GetFlagStatus(completeFlag)) {
            if(DMA_GetFlagStatus(errorFlag)) {
                DMA_ClearFlag(errorFlag);
                return errorProvider.set(ErrorProvider::ERROR_PROVIDER_DMA,E_TRANSFER_ERROR);
            }
        }

        DMA_ClearFlag(completeFlag);
        return true;
    }

    /**
     * Figure out the transfer complete flag for the current peripheral and channel.
     *
     * @return The calculated flag.
     */

    uint32_t Dma::getTransferCompleteFlag() const {

        uint32_t flag;

        flag=1L << (((_channelIndex - 1L) * 4L) + 1L);
        if(_dmaPeripheral == 2)
            flag|=0x10000000;

        return flag;
    }

    /**
     * Figure out the transfer error flag for the current peripheral and channel.
     *
     * @return The calculated flag.
     */

    uint32_t Dma::getTransferErrorFlag() const {

        uint32_t flag;

        flag=1L << (((_channelIndex - 1L) * 4L) + 3L);
        if(_dmaPeripheral == 2)
            flag|=0x10000000;

        return flag;
    }
}

/*
 * Interrupt stuff follows
 */

using namespace stm32plus;

extern "C" {

#if defined(USE_DMA1_1_INTERRUPT) || \
    defined(USE_DMA1_2_INTERRUPT) || \
    defined(USE_DMA1_3_INTERRUPT) || \
    defined(USE_DMA1_4_INTERRUPT) || \
    defined(USE_DMA1_5_INTERRUPT) || \
    defined(USE_DMA1_6_INTERRUPT) || \
    defined(USE_DMA1_7_INTERRUPT) || \
    defined(USE_DMA2_1_INTERRUPT) || \
    defined(USE_DMA2_2_INTERRUPT) || \
    defined(USE_DMA2_3_INTERRUPT) || \
    defined(USE_DMA2_4_5_INTERRUPT)

    /**
     * Handle a DMA IRQ request
     */

    static void handleIRQ(Dma* dma,uint32_t completeFlag,uint32_t halfFlag,uint32_t errorFlag) {

        // declare the event structure and fill in the pointer to the DMA class managing this transfer

        Dma::InterruptEvent event;
        event.dma=dma;

        // check for transfer complete

        if(DMA_GetITStatus(completeFlag) != RESET) {

            // set the interrupt flag in the event and notify observers

            event.interruptFlag=completeFlag;
            event.dma->notifyObservers(ObservableEvent::DMA_TransferComplete,&event);

            DMA_ClearITPendingBit(completeFlag);
        }

        // check for half transfer

        if(DMA_GetITStatus(halfFlag) != RESET) {

            // set the interrupt flag in the event and notify observers

            event.interruptFlag=halfFlag;
            event.dma->notifyObservers(ObservableEvent::DMA_HalfTransfer,&event);

            DMA_ClearITPendingBit(halfFlag);
        }

        // check for transfer error

        if(DMA_GetITStatus(errorFlag) != RESET) {

            // set the interrupt flag in the event and notify observers

            event.interruptFlag=errorFlag;
            event.dma->notifyObservers(ObservableEvent::DMA_TransferError,&event);

            DMA_ClearITPendingBit(errorFlag);
        }
    }
#endif
#if defined(USE_DMA1_1_INTERRUPT)

    /**
     * DMA1, channel 1 IRQ handler
     */

    void DMA1_Channel1_IRQHandler(void) {
        handleIRQ(Dma::Dma1_ChannelHandlers[0],DMA1_IT_TC1,DMA1_IT_HT1,DMA1_IT_TE1);
    }

#endif
#if defined(USE_DMA1_2_INTERRUPT)

/**
 * DMA1, channel 2 IRQ handler
 */

void DMA1_Channel2_IRQHandler(void) {
    handleIRQ(Dma::Dma1_ChannelHandlers[1],DMA1_IT_TC2,DMA1_IT_HT2,DMA1_IT_TE2);
}

#endif
#if defined(USE_DMA1_3_INTERRUPT)

/**
 * DMA1, channel 3 IRQ handler
 */

void DMA1_Channel3_IRQHandler(void) {
    handleIRQ(Dma::Dma1_ChannelHandlers[2],DMA1_IT_TC3,DMA1_IT_HT3,DMA1_IT_TE3);
}

#endif
#if defined(USE_DMA1_4_INTERRUPT)

/**
 * DMA1, channel 4 IRQ handler
 */

void DMA1_Channel4_IRQHandler(void) {
    handleIRQ(Dma::Dma1_ChannelHandlers[3],DMA1_IT_TC4,DMA1_IT_HT4,DMA1_IT_TE4);
}

#endif
#if defined(USE_DMA1_5_INTERRUPT)

/**
 * DMA1, channel 5 IRQ handler
 */

void DMA1_Channel5_IRQHandler(void) {
    handleIRQ(Dma::Dma1_ChannelHandlers[4],DMA1_IT_TC5,DMA1_IT_HT5,DMA1_IT_TE5);
}

#endif
#if defined(USE_DMA1_6_INTERRUPT)

/**
 * DMA1, channel 6 IRQ handler
 */

void DMA1_Channel6_IRQHandler(void) {
    handleIRQ(Dma::Dma1_ChannelHandlers[5],DMA1_IT_TC6,DMA1_IT_HT6,DMA1_IT_TE6);
}

#endif
#if defined(USE_DMA1_7_INTERRUPT)

/**
 * DMA1, channel 7 IRQ handler
 */

void DMA1_Channel7_IRQHandler(void) {
    handleIRQ(Dma::Dma1_ChannelHandlers[6],DMA1_IT_TC7,DMA1_IT_HT7,DMA1_IT_TE7);
}

#endif
#if defined(USE_DMA2_1_INTERRUPT)

/**
 * DMA2, channel 1 IRQ handler
 */

void DMA2_Channel1_IRQHandler(void) {
    handleIRQ(Dma::Dma2_ChannelHandlers[0],DMA2_IT_TC1,DMA2_IT_HT1,DMA2_IT_TE1);
}

#endif
#if defined(USE_DMA2_2_INTERRUPT)

/**
 * DMA2, channel 2 IRQ handler
 */

void DMA2_Channel2_IRQHandler(void) {
    handleIRQ(Dma::Dma2_ChannelHandlers[1],DMA2_IT_TC2,DMA2_IT_HT2,DMA2_IT_TE2);
}

#endif
#if defined(USE_DMA2_3_INTERRUPT)

/**
 * DMA2, channel 3 IRQ handler
 */

void DMA2_Channel3_IRQHandler(void) {
    handleIRQ(Dma::Dma2_ChannelHandlers[2],DMA2_IT_TC3,DMA2_IT_HT3,DMA2_IT_TE3);
}

#endif
#if defined(USE_DMA2_4_5_INTERRUPT)

/**
 * DMA2, channels 4,5 IRQ handler
 */

void DMA2_Channel4_5_IRQHandler(void) {
    handleIRQ(Dma::Dma2_ChannelHandlers[3],DMA2_IT_TC4,DMA2_IT_HT4,DMA2_IT_TE4);
    handleIRQ(Dma::Dma2_ChannelHandlers[4],DMA2_IT_TC5,DMA2_IT_HT5,DMA2_IT_TE5);
}

#endif
}
