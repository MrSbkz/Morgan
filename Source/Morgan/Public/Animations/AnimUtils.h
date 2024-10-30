#pragma once

class AnimUtils
{
public:
	template <typename T>
	static T* FindAnimNotifyByClass(UAnimSequenceBase* Animation)
	{
		if (!Animation) return nullptr;

		for (FAnimNotifyEvent NotifyEvent : Animation->Notifies)
		{
			if (T* AnimNotify = Cast<T>(NotifyEvent.Notify))
			{
				return AnimNotify;
			}
		}

		return nullptr;
	}
};
