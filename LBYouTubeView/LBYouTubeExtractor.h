//
//  LBYouTubeExtractor.h
//  LBYouTubeView
//
//  Created by Laurin Brandner on 28.09.12.
//
//

#import <Foundation/Foundation.h>

extern NSString* const LBYouTubePlayerExtractorErrorDomain;
extern NSInteger const LBYouTubePlayerExtractorErrorCodeInvalidHTML;
extern NSInteger const LBYouTubePlayerExtractorErrorCodeNoStreamURL;
extern NSInteger const LBYouTubePlayerExtractorErrorCodeNoJSONData;

extern NSInteger const LBYouTubePlayerExtractorDefaultTag;

typedef void (^LBYouTubeExtractorCompletionBlock)(NSURL *videoURL, NSError *error);
typedef void (^LBYouTubeExtractorTaggedCompletionBlock)(NSInteger tag, NSURL *videoURL, NSError *error);

typedef enum {
    LBYouTubeVideoQualitySmall    = 0,
    LBYouTubeVideoQualityMedium   = 1,
    LBYouTubeVideoQualityLarge    = 2,
} LBYouTubeVideoQuality;

@protocol LBYouTubeExtractorDelegate;

@interface LBYouTubeExtractor : NSObject

@property (nonatomic) NSInteger tag;
@property (nonatomic, readonly) LBYouTubeVideoQuality quality;
@property (nonatomic, strong, readonly) NSURL *youTubeURL;
@property (nonatomic, strong, readonly) NSURL *extractedURL;
@property (nonatomic, strong) LBYouTubeExtractorCompletionBlock completionBlock;
@property (nonatomic, strong) LBYouTubeExtractorTaggedCompletionBlock taggedCompletionBlock;
@property (nonatomic, unsafe_unretained) IBOutlet id <LBYouTubeExtractorDelegate> delegate;

-(id)initWithURL:(NSURL *)videoURL quality:(LBYouTubeVideoQuality)quality;
-(id)initWithURL:(NSURL *)videoURL quality:(LBYouTubeVideoQuality)quality andTag:(NSInteger)tag;

-(id)initWithID:(NSString *)videoID quality:(LBYouTubeVideoQuality)quality;
-(id)initWithID:(NSString *)videoID quality:(LBYouTubeVideoQuality)quality andTag:(NSInteger)tag;

-(void)startExtracting;
-(void)stopExtracting;

-(void)extractVideoURLWithCompletionBlock:(LBYouTubeExtractorCompletionBlock)completionBlock;
-(void)extractVideoURLWithTaggedCompletionBlock:(LBYouTubeExtractorTaggedCompletionBlock)completionBlock;
-(void)extractVideoURLWithTag:(NSInteger)tag andTaggedCompletionBlock:(LBYouTubeExtractorTaggedCompletionBlock)completionBlock;

@end

@protocol LBYouTubeExtractorDelegate <NSObject>

@optional
-(void)youTubeExtractor:(LBYouTubeExtractor *)extractor didSuccessfullyExtractYouTubeURL:(NSURL *)videoURL;
-(void)youTubeExtractor:(LBYouTubeExtractor *)extractor didSuccessfullyExtractYouTubeURL:(NSURL *)videoURL withTag:(NSInteger)tag;
-(void)youTubeExtractor:(LBYouTubeExtractor *)extractor failedExtractingYouTubeURLWithError:(NSError *)error;
-(void)youTubeExtractor:(LBYouTubeExtractor *)extractor failedExtractingYouTubeURLWithError:(NSError *)error andTag:(NSInteger)tag;

@end
