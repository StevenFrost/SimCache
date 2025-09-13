import { IconElement, TVNode } from "@efb/efb-api";
import { FSComponent, MappedSubscribable, Subscribable, DisplayComponent } from "@microsoft/msfs-sdk";
import "./StarRating.scss";

interface StarRatingProps {
  rating: Subscribable<number>;
}

export class StarRating extends DisplayComponent<StarRatingProps> {
  private readonly Star_NoMargin = "coui://html_UI/VFS/components/shared/resources/Icons/Marketplace/Star_NoMargin.svg";
  private readonly Star_Outline_NoMargin = "coui://html_UI/VFS/components/shared/resources/Icons/Marketplace/Star_Outline_NoMargin.svg";

  private rating_text: MappedSubscribable<string>;
  private star_1: MappedSubscribable<string>;
  private star_2: MappedSubscribable<string>;
  private star_3: MappedSubscribable<string>;
  private star_4: MappedSubscribable<string>;
  private star_5: MappedSubscribable<string>;

  constructor(args: any) {
    super(args);
    const getStar = (pos: number, rating: number): string => pos <= rating ? this.Star_NoMargin : this.Star_Outline_NoMargin;
    this.star_1 = this.props.rating.map(n => getStar(1, n));
    this.star_2 = this.props.rating.map(n => getStar(2, n));
    this.star_3 = this.props.rating.map(n => getStar(3, n));
    this.star_4 = this.props.rating.map(n => getStar(4, n));
    this.star_5 = this.props.rating.map(n => getStar(5, n));
    this.rating_text = this.props.rating.map(n => {
        return `Rating indicating ${n} out of 5 stars`;
    });
  }

  public render(): TVNode<HTMLSpanElement> {
    return (
      <div class="star-rating" aria-label={this.rating_text}>
        <IconElement url={this.star_1} />
        <IconElement url={this.star_2} />
        <IconElement url={this.star_3} />
        <IconElement url={this.star_4} />
        <IconElement url={this.star_5} />
      </div>
    );
  }
}
