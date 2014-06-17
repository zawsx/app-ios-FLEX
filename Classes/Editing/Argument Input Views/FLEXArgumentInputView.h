//
//  FLEXArgumentInputView.h
//  Flipboard
//
//  Created by Ryan Olson on 5/30/14.
//  Copyright (c) 2014 Flipboard. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSUInteger, FLEXArgumentInputViewSize) {
    FLEXArgumentInputViewSizeDefault = 0,
    FLEXArgumentInputViewSizeLarge
};

@protocol FLEXArgumentInputViewDelegate;

@interface FLEXArgumentInputView : UIView

- (instancetype)initWithArgumentTypeEncoding:(const char *)typeEncoding;

/// The name of the field. Optional (can be nil).
@property (nonatomic, copy) NSString *title;

/// To populate the filed with an initial value, set this property.
/// To reteive the value input by the user, access the property.
/// Primitive types and structs should/will be boxed in NSValue containers.
/// Concrete subclasses *must* override both the setter and getter for this property.
@property (nonatomic) id inputValue;

/// Setting this value to large will make some argument input views increase the size of their input field(s).
/// Useful to increase the use of space if there is only one input view on screen (i.e. for property and ivar editing).
@property (nonatomic, assign) FLEXArgumentInputViewSize targetSize;

/// Users of the input view can get delegate callbacks for incremental changes in user input.
@property (nonatomic, weak) id <FLEXArgumentInputViewDelegate> delegate;

// Subclasses can override

/// If the input view has one or more text views, returns YES when one of them is focused.
@property (nonatomic, readonly) BOOL inputViewIsFirstResponder;

/// For subclasses to indicate that they can handle editing a field the give type and value.
/// Used by FLEXArgumentInputViewFactory to create appropriate input views.
+ (BOOL)supportsObjCType:(const char *)type withCurrentValue:(id)value;

// For subclass eyes only

@property (nonatomic, strong, readonly) UILabel *titleLabel;
@property (nonatomic, assign, readonly) const char *typeEncoding;
@property (nonatomic, readonly) BOOL showsTitle;
+ (CGFloat)titleBottomPadding;

@end

@protocol FLEXArgumentInputViewDelegate <NSObject>

- (void)argumentInputViewValueDidChange:(FLEXArgumentInputView *)argumentInputView;

@end
