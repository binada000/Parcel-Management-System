# Smart City Logistics & Delivery System

A console-based application written in C designed to streamline parcel tracking, vehicle fleet management, rider assignments, city hubs, and delivery route optimization for urban logistics operations.

## Features

- **Parcel Management**: Add, view, search, update delivery status, and remove parcels.
- **Fleet Management**: Register vehicles (Vans, Bikes), check real-time availability, and filter vehicles by type.
- **Rider Management**: Track delivery personnel, manage contact info, availability, and assign coverage zones.
- **Hub Operations**: Maintain city hubs, zone mappings, and manager assignments.
- **Route Optimization & Cost Estimation**: Create delivery routes connecting parcels, riders, and vehicles, calculate automated delivery costs based on distance (LKR base + per km rates), mark routes completed, and sort routes by distance.

## How to Compile and Run

1. Open your terminal or command prompt in the project root folder.
2. Compile the source code using GCC:
   ```bash
   gcc PMS.c -o PMS
