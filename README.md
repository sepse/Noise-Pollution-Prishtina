# Urban Sensing - Noise Pollution :closed_book: :loud_sound:

How loud is my city - measuring noise levels in Prishtina.

## Introduction
Analyzing urban noise pollution data is an interesting data science project because it is a significant issue in urban areas worldwide. High levels of noise pollution can cause a variety of health issues, such as hearing damage, sleep disturbance, cardiovascular problems, and stress.

Data analysis of noise levels can provide valuable insights into the sources of noise and it's impact on people's health and quality of life. It can help identify areas where noise levels are highest and where measures need to be taken to reduce noise pollution.

Moreover, understanding this phenomenon leads to the development of effective noise reduction strategies, such as urban planning and policy changes. This, in turn, can lead to a reduction in noise levels, improved public health and well-being, and better quality of life in urban areas.

## Objective

Recently in Prishtina, a 'Citizen Science' research project was conducted whereby technology enthusiasts built microphone sensors that can measure sound intensity and save the data to the cloud, as a means of better understanding this phenomenon. By having access to raw data and open to the public, anyone can get an accurate overview of sound levels in the center of the city and potentially be able to understand patters of noise.

The data was saved on a public channel of [Thingspeak](www.thingspeak.com), a platform for storing and displaying various sensor data. 

![noisePRI](https://github.com/sepse/Noise-Pollution-Prishtina/blob/main/Graphics/noisePRI.png)

[Sensor Channel](https://thingspeak.com/channels/1922620)

The microphone sensor was placed in an urban residential and commercial location in the heart of Prishtina, at the intersection of "Bill Clinton" and "Robert Dole" streets.

![noisemap](https://github.com/sepse/Noise-Pollution-Prishtina/blob/main/Graphics/noisemap.png)

After downloading the data from the platform we will take a closer look using data science methodology, to see if we can get a better understanding.

### What is Noise?
But before we begin processing any data, we should understand what exactly is noise.
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

The data downloaded from the platform contains two columns, Time and Decibels, for the period of December 2022 - April 2023.

Dataset can be accessed via this link [Complete Datasets](https://drive.google.com/file/d/1nRqAAEYAyrLrKDBOr3Dfl6yAI0aJMxnu/view?usp=sharing)


## Methodology 

All data processing, exploration and visualization will be conducted using Python notebooks hosted in Google Colab (a free service available to all Google users). The material is available as a tool to further explore the topics and learn about noise pollution in particular, and data science in general. Notebooks will open in Colab, where you can see the research methodology performed on the dataset; notebooks also allow you to tweak them to further explore the data on you own.

The data science methodology involves the following:

- Data loading: Load the dataset into the Python notebook using a library like Pandas. The dataset should contain noise data in decibels, including time and location information.
- Data cleaning: Check for missing or duplicate values in the dataset and remove or impute them as necessary. Also, check for outliers in the data and remove them if they are not meaningful.
- Exploratory data analysis (EDA): Explore the dataset using visualization techniques to understand the patterns and relationships in the data. Plotting histograms, line plots, and scatterplots can help you identify patterns, correlations, and distributions in the data. Use visualizations to understand the temporal patterns in the data, identify areas of high noise, and explore the relationships between noise levels and other variables.
- Visualization: Use visualizations to present the results of the model, create interactive maps showing areas of high noise levels, or provide visualizations that help users understand the impact of noise on different environments.

**The notebooks:** [Noise Pollution Prishtina](https://github.com/sepse/Noise-Pollution-Prishtina/blob/main/Noise_Pollution_HS.ipynb)

## First Results

By plotting the datapoints visually we can see a general pattern that occurs throughout the day/night cycle, which is not surprising. What is interesting though is seeing where the majority of the datapoints rests, namely where is the average baseline.

![noiselevel](https://github.com/sepse/Noise-Pollution-Prishtina/blob/main/Graphics/noise_levels.png)

The visuals do tell a clear story as to what is the current state of noise pollution in the city, and is without a doubt the most intuitive way of conveying this kind of information. Furthermore, by performing basic statistical analysis we can also see the likelihood of certain noise levels that occur, as a way of understanging pattern of a phenomenon. 

![stats](https://github.com/sepse/Noise-Pollution-Prishtina/blob/main/Graphics/stats.png)

Looking at the mean average for this timepriod we can see that it exceeds the recommended levels, reffering to the abovementioned WHO guidelines for residential areas, though not excessively so. What is of concern as well is the outlier cases where there are dramatic increase in noise. This research ought to raise questions about the particular state of this urban environment, and increase institutional awareness about potential causes/solutions.

Potential causes could be:

- Transportation: The most common source of urban noise pollution is transportation, including cars, buses, trains, airplanes, and construction equipment. Traffic noise can be especially problematic in areas with high volumes of vehicles.
- Industrial activities: Industrial activities, such as manufacturing and construction, can generate high levels of noise pollution. Machinery, generators, and compressors are some of the sources of noise in these settings.
- Commercial activities: Commercial activities, such as entertainment venues, restaurants, and bars, can also contribute to noise pollution. Loud music, shouting, and cheering can all contribute to high noise levels.
- Urban infrastructure: Infrastructure, such as airports, highways, and railways, can generate significant noise pollution. Noise from these sources can be especially problematic for residents living near these facilities.
- Natural events: Natural events such as thunderstorms, wind, and wildlife can also contribute to noise pollution in urban areas.
- Human activities: Human activities such as shouting, playing loud music or using power tools outdoors can also contribute to urban noise pollution, especially in residential areas.

In summary, urban noise pollution can arise from a variety of sources, and it is important to identify the main sources of noise pollution in specific urban settings to effectively reduce its impact on human health and well-being.

***For more detailed view on this research, please open the Notebooks, where more granular information is available in the visual and statistical form.***

**The Notebooks:** [Noise Pollution Prishtina](https://github.com/sepse/Noise-Pollution-Prishtina/blob/main/Noise_Pollution_HS.ipynb)

