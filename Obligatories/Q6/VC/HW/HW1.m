noDefects = imread('Blispac1.tif');
defects = imread('Blispac2.tif');
figure, imshow(defects), title('Blispac with defects');
figure, imshow(noDefects), title('Blispac with no defects');
gray_defects = rgb2gray(defects);
% Suavizar la imagen
lap = fspecial('laplacian');
soft_defects = imfilter(double(gray_defects), lap, 'conv');
figure, imshow(abs(soft_defects)), title('Imagen suavizada (defectuosas)');

% Pasarla a gris y binarizarla

bin_defects = imbinarize(gray_defects);
s = regionprops(bin_defects, 'Centroid');
centroids = cat(1,s.Centroid);
imshow(bin_defects), title('Imagen binarizada (defectuosas)');
hold on;
plot(centroids(:,1), centroids(:,2), 'b*')
hold off;