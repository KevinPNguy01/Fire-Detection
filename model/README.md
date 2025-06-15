# Fire and Smoke Detection using YOLOv8

Real-time fire and smoke detection using YOLOv8. Trained on multiple aggregated datasets. This repo contains a notebook demonstrating usage and performance of the model in both image and video detection. 

## Datasets Used
[YOLOv8-Fire-and-Smoke-Detection](https://github.com/Abonia1/YOLOv8-Fire-and-Smoke-Detection) (Small dataset for fire and smoke)

[DFireDataset](https://github.com/gaiasd/DFireDataset) (Large dataset for fire and smoke)

[yolov5-fire-detection](https://github.com/spacewalk01/yolov5-fire-detection) (Medium dataset for fire only)


### Combined Dataset
I have aggregated the above datasets into a single dataset that can be downloaded here:

[Aggregated Dataset](https://drive.google.com/file/d/14KOvHkB3z-txUeyITVZnyM0zKAADfcKs/view?usp=sharing)

## Images
![Prediction on Multiple Images](demos/batch_images.jpg "Prediction on Multiple Images")

## Videos

### Firefighting
![Firefighters Indoors](demos/firefighter_detections.gif "Firefighters Indoors")

![Firefighters Outdoors](demos/firefighter2_detections.gif "Firefighters Outdoors")

### Indoors
![Bedroom Fire](demos/bedroom_detections.gif "Bedroom Fire")

![Living Room](demos/living_room_detections.gif "Living Room Fire")

### Outdoors
![Wildfire](demos/wildfire_detections.gif "Wildfire")

![Civic Stadium Fire](demos/civic_stadium_detections.gif "Civic Stadium Fire")