/*
 *  Copyright (c) 2014-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#import <AsyncDisplayKit/ASLayoutSpec.h>

/** The direction children are stacked in */
typedef NS_ENUM(NSUInteger, ASStackLayoutDirection) {
  /** Children are stacked vertically */
  ASStackLayoutDirectionVertical,
  /** Children are stacked horizontally */
  ASStackLayoutDirectionHorizontal,
};

/** If no children are flexible, how should this spec justify its children in the available space? */
typedef NS_ENUM(NSUInteger, ASStackLayoutJustifyContent) {
  /**
   On overflow, children overflow out of this spec's bounds on the right/bottom side.
   On underflow, children are left/top-aligned within this spec's bounds.
   */
  ASStackLayoutJustifyContentStart,
  /**
   On overflow, children are centered and overflow on both sides.
   On underflow, children are centered within this spec's bounds in the stacking direction.
   */
  ASStackLayoutJustifyContentCenter,
  /**
   On overflow, children overflow out of this spec's bounds on the left/top side.
   On underflow, children are right/bottom-aligned within this spec's bounds.
   */
  ASStackLayoutJustifyContentEnd,
};

/** Orientation of children along cross axis */
typedef NS_ENUM(NSUInteger, ASStackLayoutAlignItems) {
  /** Align children to start of cross axis */
  ASStackLayoutAlignItemsStart,
  /** Align children with end of cross axis */
  ASStackLayoutAlignItemsEnd,
  /** Center children on cross axis */
  ASStackLayoutAlignItemsCenter,
  /** Expand children to fill cross axis */
  ASStackLayoutAlignItemsStretch,
};


/**
 A simple layout spec that stacks a list of children vertically or horizontally.

 - All children are initially laid out with the an infinite available size in the stacking direction.
 - In the other direction, this spec's constraint is passed.
 - The children's sizes are summed in the stacking direction.
   - If this sum is less than this spec's minimum size in stacking direction, children with flexGrow are flexed.
   - If it is greater than this spec's maximum size in the stacking direction, children with flexShrink are flexed.
   - If, even after flexing, the sum is still greater than this spec's maximum size in the stacking direction,
     justifyContent determines how children are laid out.

 For example:
 
 - Suppose stacking direction is Vertical, min-width=100, max-width=300, min-height=200, max-height=500.
 - All children are laid out with min-width=100, max-width=300, min-height=0, max-height=INFINITY.
 - If the sum of the childrens' heights is less than 200, children with flexGrow are flexed larger.
 - If the sum of the childrens' heights is greater than 500, children with flexShrink are flexed smaller.
   Each child is shrunk by `((sum of heights) - 500)/(number of flexShrink-able children)`.
 - If the sum of the childrens' heights is greater than 500 even after flexShrink-able children are flexed,
   justifyContent determines how children are laid out.
 */
@interface ASStackLayoutSpec : ASLayoutSpec

/** Specifies the direction children are stacked in. */
@property (nonatomic, assign) ASStackLayoutDirection direction;
/** The amount of space between each child. */
@property (nonatomic, assign) CGFloat spacing;
/** The amount of space between each child. */
@property (nonatomic, assign) ASStackLayoutJustifyContent justifyContent;
/** Orientation of children along cross axis */
@property (nonatomic, assign) ASStackLayoutAlignItems alignItems;

- (instancetype)init;

/**
 @param direction The direction of the stack view (horizontal or vertical)
 @param spacing The spacing between the children
 @param justifyContent If no children are flexible, this describes how to fill any extra space
 @param alignItems Orientation of the children along the cross axis
 @param children ASLayoutable children to be positioned.
 */
+ (instancetype)stackLayoutSpecWithDirection:(ASStackLayoutDirection)direction spacing:(CGFloat)spacing justifyContent:(ASStackLayoutJustifyContent)justifyContent alignItems:(ASStackLayoutAlignItems)alignItems children:(NSArray *)children;

- (void)addChild:(id<ASLayoutable>)child;
- (void)addChildren:(NSArray *)children;

@end
