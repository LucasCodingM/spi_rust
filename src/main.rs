#![no_main]
#![no_std]

use cortex_m_semihosting::hprintln;
use panic_halt as _;

use cortex_m_rt::entry;
use stm32f4xx_hal::{
    prelude::*,
    spi::{Mode, Phase, Polarity, Spi},
    gpio::{gpioa::PA4, Output, PushPull},
    pac,
};

//use cortex_m_semihosting::{hprintln};

#[entry]
fn main() -> ! {
    let dp = pac::Peripherals::take().unwrap();
   

    let rcc = dp.RCC.constrain();
    let clocks = rcc.cfgr.freeze();

    let mut delay = dp.TIM2.delay_ms(&clocks);

    /* The GPIO pins are organised into groups of 16 pins which can be accessed through the gpioa, gpiob… modules.
     To get access to the pins, you first need to convert them into a HAL designed struct from the pac struct using the split function. */
    let gpioa = dp.GPIOA.split();
    let gpiob = dp.GPIOB.split();

    // Set up PA4 as software-controlled SS
    // This gives you a struct containing all the pins px0..px15. By default pins are in floating input mode. You can change their modes. 
    let mut ss: PA4<Output<PushPull>> = gpioa.pa4.into_push_pull_output();
    ss.set_high(); // Not selected initially

    // SPI1 pins: SCK, MISO, MOSI
    // These are the Pins for SPI take a look to datasheet [https://www.st.com/resource/en/datasheet/stm32f407vg.pdf]
    let sck = gpiob.pb3.into_alternate::<5>();
    let miso= gpiob.pb4.into_alternate::<5>();
    let mosi= gpiob.pb5.into_alternate::<5>();

    // SPI Master setup
   
    let mut spi = Spi::new(
        dp.SPI1,
        (sck, miso, mosi),
 /* Mode 0 (the default) − Clock is normally low (CPOL = 0), and the data is sampled on the transition from low to high (leading edge) (CPHA = 0).
    Mode 2 − Clock is normally high (CPOL = 1), and the data is sampled on the transition from high to low (leading edge) (CPHA = 0).
    Mode 1 − Clock is normally low (CPOL = 0), and the data is sampled on the transition from high to low (trailing edge) (CPHA = 1).
    Mode 3 − Clock is normally high (CPOL = 1), and the data is sampled on the transition from low to high (trailing edge) (CPHA = 1). */
        Mode {
            polarity: Polarity::IdleLow,
            phase: Phase::CaptureOnSecondTransition,
        },
        10.kHz(),
        &clocks,
    );

    let message = b"Hello World\n";
    ss.set_high(); // Disable slave select

    loop {
        // Send data
    ss.set_low(); // Enable slave select
    
    spi.write(message).unwrap();
    ss.set_high(); // Disable the slave select
    
    hprintln!("Wait 1s");
    delay.delay_ms(1000u32); // 1000 milliseconds (1 second)
    
    }

}
