# Cerebro comercial

## Authors
### Names
- Bosque Huertas, Edgar
- Escribano Sierra, Marc
- Metcalf Quintana, Sergi
- Morais Caldas, David

### Email
- edgar.bosque@estudiantat.upc.edu
- marc.escribano.sierra@estudiantat.upc.edu
- sergi.metcalf@estudiantat.upc.edu
- david.morais@estudiantat.upc.edu

## Description
This is a software project developed as part of the PROP (Programming Projects) course. Uses the three-tier architecture.

### Key Features
- **Product Management**: Complete CRUD (Create, read, update and delete) operations for product catalog
- **Similarity Management**: Handle and maintain product relationship metrics
- **Distribution Algorithms**: 
  - Basic solution (brute force approach)
  - 2-Approximation algorithm
  - Hill climbing algorithm
  - Iterated local search algorithm
- **Solution Modification**: Ability to modify proposed distributions
- **Data Handling**: Support both manual input and file import/export

### Technical Approach
The system calculates optimal product placement by considering:
- Product relationships and similarity scores
- Circular rack layout constraints
- Customer purchase probability optimization 

## Getting Started
### Prerequisites
- Java Development Kit 22 (JDK)
- Gradle (for building)

## Project Structure
```
subgrup-prop32.3/
├── DOCS/           # Project documentation
├── EXE/            # Executable files and test data
├── FONT/           # Source code
│   ├── src/
│   │   ├── main/java/    # Main source files
│   │   └── test/java/    # Test files
│   └── README.md
├── build.gradle    # Gradle build configuration
└── README.md      # Project overview
```

## Usage
Go to the root directory of the project and run the following commands:

- To run the application

It's recommended to run the application with the following command to avoid any issues with the GUI:
```
./gradlew run --console plain
```
- To run the tests
```
./gradlew test
```
- To build the project
```
./gradlew build
```
It will create a folder called `build` on the `EXE` directory with the compiled classes and the JAR file.
- To generate the documentation
```
./gradlew javadoc
```
It will create a folder called `javadoc` on the `DOCS` directory with the documentation.

