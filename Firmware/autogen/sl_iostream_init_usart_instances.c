#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
#include "sl_power_manager.h"
#endif
#include "em_device.h"
#include "sl_iostream.h"
#include "sl_iostream_uart.h"
#include "sl_iostream_usart.h"


// Include instance config 
 #include "sl_iostream_usart_iouart_config.h"

// MACROs for generating name and IRQ handler function  
#define SL_IOSTREAM_USART_CONCAT_PASTER(first, second, third)        first ##  second ## third
 



#define SL_IOSTREAM_USART_TX_IRQ_NUMBER(periph_nbr)     SL_IOSTREAM_USART_CONCAT_PASTER(USART, periph_nbr, _TX_IRQn)        
#define SL_IOSTREAM_USART_RX_IRQ_NUMBER(periph_nbr)     SL_IOSTREAM_USART_CONCAT_PASTER(USART, periph_nbr, _RX_IRQn)        
#define SL_IOSTREAM_USART_TX_IRQ_HANDLER(periph_nbr)    SL_IOSTREAM_USART_CONCAT_PASTER(USART, periph_nbr, _TX_IRQHandler)  
#define SL_IOSTREAM_USART_RX_IRQ_HANDLER(periph_nbr)    SL_IOSTREAM_USART_CONCAT_PASTER(USART, periph_nbr, _RX_IRQHandler)  

#define SL_IOSTREAM_USART_RX_DMA_SIGNAL(periph_nbr)     SL_IOSTREAM_USART_CONCAT_PASTER(dmadrvPeripheralSignal_USART, periph_nbr, _RXDATAV)  

#define SL_IOSTREAM_USART_CLOCK_REF(periph_nbr)         SL_IOSTREAM_USART_CONCAT_PASTER(cmuClock_, USART, periph_nbr)       
// EM Events
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT) 
#if defined(_SILICON_LABS_32B_SERIES_2)
#define SLEEP_EM_EVENT_MASK      ( SL_POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM2  \
                                  | SL_POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM2  \
                                  | SL_POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM3 \
                                  | SL_POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM3  \
                                  | SL_POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM0)
#else 
#define SLEEP_EM_EVENT_MASK      (SL_POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM0)
#endif // _SILICON_LABS_32B_SERIES_2
static void events_handler(sl_power_manager_em_t from,
                           sl_power_manager_em_t to);
static sl_power_manager_em_transition_event_info_t events_info =
{
  .event_mask = SLEEP_EM_EVENT_MASK,
  .on_event = events_handler,
};
static sl_power_manager_em_transition_event_handle_t events_handle;
#endif // SL_CATALOG_POWER_MANAGER_PRESENT


sl_status_t sl_iostream_usart_init_iouart(void);


// Instance(s) handle and context variable 

static sl_iostream_uart_t sl_iostream_iouart;
sl_iostream_t *sl_iostream_iouart_handle = &sl_iostream_iouart.stream;
sl_iostream_uart_t *sl_iostream_uart_iouart_handle = &sl_iostream_iouart;
static sl_iostream_usart_context_t  context_iouart;
static uint8_t  rx_buffer_iouart[SL_IOSTREAM_USART_IOUART_RX_BUFFER_SIZE];
sl_iostream_instance_info_t sl_iostream_instance_iouart_info = {
  .handle = &sl_iostream_iouart.stream,
  .name = "iouart",
  .type = SL_IOSTREAM_TYPE_UART,
  .periph_id = SL_IOSTREAM_USART_IOUART_PERIPHERAL_NO,
  .init = sl_iostream_usart_init_iouart,
};



sl_status_t sl_iostream_usart_init_iouart(void)
{
  sl_status_t status;
  USART_InitAsync_TypeDef init_iouart = USART_INITASYNC_DEFAULT;
  init_iouart.baudrate = SL_IOSTREAM_USART_IOUART_BAUDRATE;
  init_iouart.parity = SL_IOSTREAM_USART_IOUART_PARITY;
  init_iouart.stopbits = SL_IOSTREAM_USART_IOUART_STOP_BITS;
#if (_SILICON_LABS_32B_SERIES > 0)
  init_iouart.hwFlowControl = SL_IOSTREAM_USART_IOUART_FLOW_CONTROL_TYPE != uartFlowControlSoftware ? SL_IOSTREAM_USART_IOUART_FLOW_CONTROL_TYPE : usartHwFlowControlNone;
#endif
  sl_iostream_usart_config_t config_iouart = { 
    .usart = SL_IOSTREAM_USART_IOUART_PERIPHERAL,
    .clock = SL_IOSTREAM_USART_CLOCK_REF(SL_IOSTREAM_USART_IOUART_PERIPHERAL_NO),
    .tx_port = SL_IOSTREAM_USART_IOUART_TX_PORT,
    .tx_pin = SL_IOSTREAM_USART_IOUART_TX_PIN,
    .rx_port = SL_IOSTREAM_USART_IOUART_RX_PORT,
    .rx_pin = SL_IOSTREAM_USART_IOUART_RX_PIN,
#if (_SILICON_LABS_32B_SERIES > 0)
#if defined(SL_IOSTREAM_USART_IOUART_CTS_PORT)
    .cts_port = SL_IOSTREAM_USART_IOUART_CTS_PORT,
    .cts_pin = SL_IOSTREAM_USART_IOUART_CTS_PIN,
#endif
#if defined(SL_IOSTREAM_USART_IOUART_RTS_PORT)
    .rts_port = SL_IOSTREAM_USART_IOUART_RTS_PORT,
    .rts_pin = SL_IOSTREAM_USART_IOUART_RTS_PIN,
#endif
#endif
#if defined(GPIO_USART_ROUTEEN_TXPEN)
    .usart_index = SL_IOSTREAM_USART_IOUART_PERIPHERAL_NO,
#elif defined(USART_ROUTEPEN_RXPEN)
    .usart_tx_location = SL_IOSTREAM_USART_IOUART_TX_LOC,
    .usart_rx_location = SL_IOSTREAM_USART_IOUART_RX_LOC,
#if defined(SL_IOSTREAM_USART_IOUART_CTS_PORT)
    .usart_cts_location = SL_IOSTREAM_USART_IOUART_CTS_LOC,
#endif
#if defined(SL_IOSTREAM_USART_IOUART_RTS_PORT)
    .usart_rts_location = SL_IOSTREAM_USART_IOUART_RTS_LOC,
#endif
#else
    .usart_location = SL_IOSTREAM_USART_IOUART_ROUTE_LOC,
#endif
  };

  sl_iostream_dma_config_t dma_config_iouart = {.src = (uint8_t *)&SL_IOSTREAM_USART_IOUART_PERIPHERAL->RXDATA,
                                                        .peripheral_signal = SL_IOSTREAM_USART_RX_DMA_SIGNAL(SL_IOSTREAM_USART_IOUART_PERIPHERAL_NO)};

  sl_iostream_uart_config_t uart_config_iouart = {
    .dma_cfg = dma_config_iouart,
    .rx_buffer = rx_buffer_iouart,
    .rx_buffer_length = SL_IOSTREAM_USART_IOUART_RX_BUFFER_SIZE,
    .tx_irq_number = SL_IOSTREAM_USART_TX_IRQ_NUMBER(SL_IOSTREAM_USART_IOUART_PERIPHERAL_NO),
    .rx_irq_number = SL_IOSTREAM_USART_RX_IRQ_NUMBER(SL_IOSTREAM_USART_IOUART_PERIPHERAL_NO),
    .lf_to_crlf = SL_IOSTREAM_USART_IOUART_CONVERT_BY_DEFAULT_LF_TO_CRLF,
    .rx_when_sleeping = SL_IOSTREAM_USART_IOUART_RESTRICT_ENERGY_MODE_TO_ALLOW_RECEPTION,
  };
  uart_config_iouart.sw_flow_control = SL_IOSTREAM_USART_IOUART_FLOW_CONTROL_TYPE == uartFlowControlSoftware;
  // Instantiate usart instance 
  status = sl_iostream_usart_init(&sl_iostream_iouart,
                                  &uart_config_iouart,
                                  &init_iouart,
                                  &config_iouart,
                                  &context_iouart);
  EFM_ASSERT(status == SL_STATUS_OK);

  

  return status;
}



void sl_iostream_usart_init_instances(void)
{
  sl_status_t status;
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
  // Enable power manager notifications
  sl_power_manager_subscribe_em_transition_event(&events_handle, &events_info);
#endif

  // Instantiate usart instance(s) 
  
  status = sl_iostream_usart_init_iouart();
  EFM_ASSERT(status == SL_STATUS_OK);
  
}

 
// IOUART IRQ Handler
void SL_IOSTREAM_USART_TX_IRQ_HANDLER(SL_IOSTREAM_USART_IOUART_PERIPHERAL_NO)(void)
{
  sl_iostream_usart_irq_handler(&sl_iostream_iouart);
}

void SL_IOSTREAM_USART_RX_IRQ_HANDLER(SL_IOSTREAM_USART_IOUART_PERIPHERAL_NO)(void)
{
  sl_iostream_usart_irq_handler(&sl_iostream_iouart);
}



#if defined(SL_CATALOG_POWER_MANAGER_PRESENT) 
#if !defined(SL_CATALOG_KERNEL_PRESENT)
 
sl_power_manager_on_isr_exit_t sl_iostream_usart_iouart_sleep_on_isr_exit(void)
{
  return sl_iostream_uart_sleep_on_isr_exit(&sl_iostream_iouart);
}

#endif // SL_CATALOG_KERNEL_PRESENT
static void events_handler(sl_power_manager_em_t from,
                           sl_power_manager_em_t to)
{
  (void) from;
  #if defined(_SILICON_LABS_32B_SERIES_2)
  uint32_t out;
  if (((from == SL_POWER_MANAGER_EM2) 
      || (from == SL_POWER_MANAGER_EM3)) 
      && ((to == SL_POWER_MANAGER_EM1) 
      || (to == SL_POWER_MANAGER_EM0))) {
      
	// Wake the USART Tx pin back up
	out = GPIO_PinOutGet(SL_IOSTREAM_USART_IOUART_TX_PORT, SL_IOSTREAM_USART_IOUART_TX_PIN);
	GPIO_PinModeSet(SL_IOSTREAM_USART_IOUART_TX_PORT, SL_IOSTREAM_USART_IOUART_TX_PIN, gpioModePushPull, out);
    
	} else if (((to == SL_POWER_MANAGER_EM2) 
			   || (to == SL_POWER_MANAGER_EM3)) 
			   && ((from == SL_POWER_MANAGER_EM1) 
			   || (from == SL_POWER_MANAGER_EM0))) {
	    
	  // Sleep the USART Tx pin on series 2 devices to save energy
      out = GPIO_PinOutGet(SL_IOSTREAM_USART_IOUART_TX_PORT, SL_IOSTREAM_USART_IOUART_TX_PIN);
      GPIO_PinModeSet(SL_IOSTREAM_USART_IOUART_TX_PORT, SL_IOSTREAM_USART_IOUART_TX_PIN, gpioModeDisabled, out);
    
  }
  #endif // _SILICON_LABS_32B_SERIES_2
  if (to < SL_POWER_MANAGER_EM2){
    // Only prepare for wakeup from EM1 or less, since USART doesn't run in EM2
     
    if (sl_iostream_uart_iouart_handle->stream.context != NULL) {
      sl_iostream_uart_prepare_for_sleep(sl_iostream_uart_iouart_handle);
    }
    
  }
}
#endif // SL_CATALOG_POWER_MANAGER_PRESENT