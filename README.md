# Urban Sensing - Noise Pollution :closed_book: :loud_sound:

Measuring noise levels in Prishtina.

## Introduction
Analyzing urban noise pollution data is an interesting data science project because noise pollution is a significant problem in urban areas worldwide. High levels of noise pollution can cause a variety of health issues, such as hearing damage, sleep disturbance, cardiovascular problems, and stress.

Data analysis of noise pollution levels can provide valuable insights into the sources of noise pollution and the impact of noise on people's health and quality of life. It can help identify areas where noise levels are highest and where measures need to be taken to reduce noise pollution.

Moreover, understanding this phenomenon leads to the development of effective noise reduction strategies, such as urban planning and policy changes. This, in turn, can lead to a reduction in noise levels, improved public health and well-being, and better quality of life in urban areas.

## Objective

Recently in Prishtina, a 'Citizen Science' research project was conducted whereby technology enthusiasts built microphone sensors that can measure sound intensity and save the data to the cloud, as a means of better understanding this phenomenon. By having access to raw data and open to the public, anyone can get an accurate overview of sound levels in the center of the city and potentially be able to understand patters of noise.

The data was saved on a public channel of [Thingspeak](www.thingspeak.com), a platform for storing and displaying various sensor data. 

![noisePRI](https://github.com/sepse/Noise-Pollution-Prishtina/blob/main/Graphics/noisePRI.png)

[Sensor Channel](https://thingspeak.com/channels/1922620)

The microphone sensor was placed in an urban residential and commercial location in the heart of Prishtina.

![noisemap](https://github.com/sepse/Noise-Pollution-Prishtina/blob/main/Graphics/noisemap.png)

### What is Noise
The acceptable range of noise levels in decibels for urban environments depends on the type of area and its intended use. The World Health Organization (WHO) has provided guidelines for community noise levels in urban areas:

- In residential areas, the recommended outdoor noise levels during the daytime is 55 dB(A) and 40 dB(A) during the nighttime to protect the residents' health and well-being.
- In sensitive areas such as hospitals, schools, and libraries, the recommended indoor noise levels are between 35-40 dB(A) during the daytime and 30 dB(A) during the nighttime.
- In commercial areas such as shopping centers, the recommended noise levels during the daytime are between 60-65 dB(A) and 45 dB(A) during the nighttime.
- In industrial areas, the recommended noise levels during the daytime are between 70-75 dB(A) and 60 dB(A) during the nighttime.

It is essential to note that these are only guidelines, and different countries and regions may have their own regulations and standards for noise levels in urban areas.
Exposure to prolonged high noise levels can cause a wide range of health problems, including hearing loss, sleep disturbance, cardiovascular diseases, and stress. Therefore, it is crucial to monitor and control noise levels in urban areas to ensure public health and well-being. [WHO Source](https://www.who.int/europe/news-room/fact-sheets/item/noise)

![noiseLevel](https://github.com/sepse/Noise-Pollution-Prishtina/blob/main/Graphics/NOISE-LEVEL-DECIBEL-CHART.png)
-Chart [Source](https://www.electronicshub.org/noise-level-decibels-chart/)

## Data
### Noise Pollution Data

The data was downloaded from the platform, and contains two columns, Time and Decibels, for the period of December 2022 - April 2023.

Dataset can be accessed via this link [Complete Datasets](https://drive.google.com/drive/folders/1jQUcwHCfegaoPiOR3yDSgqbY3zlYsIAx?usp=sharing)


## Methodology 

**The notebooks:** [Balkan Air Pollution](https://github.com/sepse/COVAir-Balkans/blob/main/balkan_pollution.ipynb)

## First Results








![noiselevel](https://github.com/sepse/Noise-Pollution-Prishtina/blob/main/Graphics/noise_levels.png)
