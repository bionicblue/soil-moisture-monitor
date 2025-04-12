# soil-moisture-monitor
Embedded system to monitor the dryness of the soil of a plant

# Hardware
- [ESP32-DevKitC-32E](https://www.amazon.com/dp/B0D6BH4K9B?ref=ppx_yo2ov_dt_b_fed_asin_title)
- [OLED Display Screen](https://www.amazon.com/dp/B0D2RMQQHR?ref=ppx_yo2ov_dt_b_fed_asin_title)
- [Gikfun Capacitive Soil Moisture Sensor](https://www.amazon.com/dp/B07H3P1NRM?ref=ppx_yo2ov_dt_b_fed_asin_title)
- [DHT22 AM2302 Digital Temperature & Humidity Sensor](https://www.amazon.com/dp/B096LT84F6?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1)
- [3.7V/1800mAh Lithium Battery](https://www.amazon.com/dp/B09DPL8RZH?ref=ppx_yo2ov_dt_b_fed_asin_title)
- [LED](https://www.amazon.com/dp/B07PG84V17?ref=ppx_yo2ov_dt_b_fed_asin_title)
- [Slide Switch](https://www.amazon.com/dp/B09R43HCY3?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1)

# Functionality
- The OLED screen displays:
  - Humidity
  - Temperature
  - Soil moisture sensor value
  - Soil moisture sensor threshold value
  - Is the soil dry?
  - Battery life
- The deeper the soil moisture sensor goes into the dirt the different the reading is. Try and be consistent with the depth you insert it in (at least a few inches)
- Insert the sensor in dry dirt and press and hold the button. The LED will turn off (if it's on) and then hold for 5 seconds to calibrate the threshold
- When the reading is greater than the threshold it means the dirt is dry and it needs watering
- LED remains ON when the dry threshold has been breached

# TODO
- Add tests
- Add tests to CI
- Add switch to enable low power mode. Sensor readings and displaying on the screen would only happen every 30 min when enabled.
- Add notification system when the threshold is breached
- Make the screen display data look cooler
- Add solar power recharging to the battery
- Create PCB
- 3D print casing to hold everything