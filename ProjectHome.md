## Toolkit for Real Estate Data on the Android Platform ##

This toolkit is a proof of concept for creating a RETS client on the Android platform.  It includes a demo RETS client application for Android as well as a whitepaper written by Mark Scheel, the developer who built prototype and demo application.

## Demo Application ##

The application is documented and has the ability to complete five RETS transactions: Login, GetMetadata, Search, GetObject and Logout. Based on feedback from CRT, a consumer grade functional prototype that showcases the technical side of RETS through a user friendly multiple screen interface with scrolling thumbnails has been created. It includes Google Maps integration, and email capability including attached photos. Its development requires significant upgrades to the initial deliverable as it requires the download of multiple photos and listings, which in turn requires the passing of data from the Android Java software layer, down to the C/C++ Native Development Kit layer, which was previously more loosely coupled.

## White-Paper ##

The white-paper gives a detailed overview into the process of creating the demo app, including the biggest hurdles to getting libRETS installed on the Android.