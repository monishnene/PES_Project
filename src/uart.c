<type> ​ ​ UART_configure ​ ​ ();
1. Configures​ ​ UART​ ​ to​ ​ the​ ​ given​ ​ settings.
62. No hardcoded configurations may be used. All settings need to use predefined Bit Masks and
macro​ ​ functions​ ​ to​ ​ help​ ​ determine​ ​ calculated​ ​ values
<type> ​ ​ UART_send ​ ​ ( ​ ​ <data-to-send> ​ ​ );
1. This​ ​ function​ ​ will​ ​ send​ ​ a ​ ​ single​ ​ byte​ ​ down​ ​ a ​ ​ specific​ ​ UART​ ​ device
2. The​ ​ function​ ​ will​ ​ take​ ​ 1 ​ ​ argument:
a. Pointer​ ​ to​ ​ the​ ​ data​ ​ item​ ​ to​ ​ send
3. This​ ​ function​ ​ should​ ​ block​ ​ on​ ​ transmitting​ ​ data
<type> ​ ​ UART_send_n ​ ​ ( ​ ​ <data-to-send>, ​ ​ <length-of-data> ​ ​ );
1. Function​ ​ takes​ ​ 2 ​ ​ arguments
a. Pointer​ ​ to​ ​ a ​ ​ contiguous​ ​ block​ ​ of​ ​ data​ ​ that​ ​ needs​ ​ to​ ​ be​ ​ transmitted
b. Number​ ​ of​ ​ items​ ​ to​ ​ transmit
2. This​ ​ function​ ​ should​ ​ block​ ​ on​ ​ transmitting​ ​ data
<type> ​ ​ UART_receive( ​ ​ <received-data> ​ ​ );
1. This​ ​ function​ ​ should​ ​ return​ ​ a ​ ​ received​ ​ byte​ ​ on​ ​ the​ ​ UART​ ​ using​ ​ an​ ​ input​ ​ parameter​ ​ pointer.
2. This​ ​ function​ ​ should​ ​ block​ ​ until​ ​ a ​ ​ character​ ​ has​ ​ been​ ​ received.
<type> ​ ​ UART_receive_n ​ ​ ( ​ ​ <received-data>, ​ ​ <length-of-data-to-receive> ​ ​ );
1. This​ ​ function​ ​ should​ ​ receive​ ​ a ​ ​ number​ ​ of​ ​ bytes​ ​ on​ ​ the​ ​ UART.
2. Function​ ​ takes​ ​ 2 ​ ​ arguments
a. Pointer​ ​ to​ ​ a ​ ​ memory​ ​ location​ ​ to​ ​ place​ ​ data​ ​ that​ ​ is​ ​ being​ ​ received
b. Number​ ​ of​ ​ items​ ​ to​ ​ receive
3. This​ ​ function​ ​ should​ ​ block​ ​ until​ ​ a ​ ​ number​ ​ of​ ​ characters​ ​ have​ ​ been​ ​ received.
void ​ ​ UART0_IRQHandler();
1. This​ ​ function​ ​ is​ ​ the​ ​ IRQ​ ​ handler​ ​ for​ ​ the​ ​ UART.
2. You​ ​ will​ ​ need​ ​ to​ ​ handle​ ​ two​ ​ types​ ​ of​ ​ interrupts​ ​ in​ ​ this​ ​ function
a. Receive​ ​ Interrupts
b. Transmit​ ​ interrupt
3. Each​ ​ interrupt​ ​ should​ ​ clear​ ​ their​ ​ associated​ ​ flag​ ​ when​ ​ completed​ ​ but​ ​ only​ ​ if​ ​ they​ ​ were​ ​ set
4. This​ ​ routine​ ​ should​ ​ be​ ​ as​ ​ short​ ​ as​ ​ possible
