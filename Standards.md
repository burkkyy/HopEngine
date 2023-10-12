# Bunny Game Co. Code Standards
Sources:   
Some standards are borrowed from [coding standards](http://csci.viu.ca/~wesselsd/courses/csci265/standards.html). Many thanks to Dr. Dave Wessels.  
Commenting standrds are inspired by [JSDoc](https://jsdoc.app). 

## Enforcement

It is expected that developers follow these standards. Code will be checked periodically, however these standards rely largely on the honour system.  

## General Expectations

Code must compile without errors before being commited to the main repository. Code should also have minimal to no warnings. 
  
Code must not use globally defined namespaces.  
Example:
```
using namespace std //NOT ACCEPTABLE
using std::cout     //ACCEPTABLE
```
### Constants  
Hard coded constant literals should be avoided at all times. If a constant value is needed it should be defined in a header file. 

## Naming Standards

Naming conventions help make code more readable. Consistency may be frustrating in the short term but in the long term it will improve code debugging and maintance. Because of this it is essential that all code follow the naming standards.  
  
### Key Types Name Standards:
`Variables`, `Functions`, and `Parameters` and `File Names` are written in `snake_case`.  
  
`Classes` and `Types` are written in `CamelCase`.  
  
`Constants` are written in `ALL_CAPS`.  
  
It is more important that code be readable then brief. For that reason names should be as descriptive as possible within reason. A single Name should not be more then 5 words long, but a single letter is too short. If it is not clear to someone reading your code what an object does, then it's name is not clear enough. 

## Comments  

Comments should be gramatically correct and have proper punctuation when possible. The exception to this is inline comments, which may have less formal structure. 

### Header Comments
Files should have a header comment with information regarding who has worked on that file and the date it was last edited.  
Example:
```
/**
 * @Author: Author name, author name, ...
 * @Date: Date of most recent edit
 *
 */
```
### Functions  

Function commenting should take the form:
```
/**
 * @Function
 * @Name
 * @Param {Parameter Type} Parameter name - Parameter Use
 * 
 * @Description
 * @Return
 */
```

### Inline Comments  
Inline comments should be used as needed to help with code clarity. Whenever possible it is preferable to use clear variable names over comments explaining incomprehensible code.   
  
Comments should not state what the code is doing, rather help the reader understand the purpose of that section of code. 

## General Structure
Code should be indented in a consisten way within each file and line lengths should be kept a maxiumum of 100 columns. 

## Classes

Classes should always be used over Structs. 

