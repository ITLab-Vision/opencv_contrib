=========================================
Vignette
=========================================

Makes the edges of the photo less bright, creating an oval frame around its central part.

.. cpp:function:: int vignette(cv::InputArray src, cv::OutputArray dst, cv::Size rect)

   :param src: Source 8-bit three-channel image.
   :param dst: Destination image of the same size and the same type as **src**.
   :param rect: Size of rectangle describes an ellipse, whose center is at the center image.
   :return: Error code.

The algorithm.

#. Create a new 3-channel image, which is interpreted as BGR image.

#. Copy the **src** image to the **dst** image.

#. For every channel of the **dst** image calculate :math:`dist` and :math:`coefficient`, where
   :math:`dist` is an amount, which desribes a distance from the current pixel to border of the ellipse;
   :math:`coefficient` is a number which cuts a part of the channel's intensity (value is in the range :math:`[0, 1]`).

   The :math:`coefficient` is calculated by the following formula:

   .. math::

      coefficient = 1 - ((dist - 1) / radiusMax),

   where :math:`radiusMax` is a maximum distance from border of the ellipse to the most far pixel (a corner of the image).

Example.

|srcImage| |dstImage|

.. |srcImage| image:: pics/vignette_before.jpg
   :width: 40%

.. |dstImage| image:: pics/vignette_after.jpg
   :width: 40%
